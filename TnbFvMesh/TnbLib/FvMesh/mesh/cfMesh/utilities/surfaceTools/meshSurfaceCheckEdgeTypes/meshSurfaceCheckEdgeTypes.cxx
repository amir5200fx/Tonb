#include <meshSurfaceCheckEdgeTypes.hxx>

#include <meshSurfaceCheckInvertedVertices.hxx>
#include <meshSurfaceEngine.hxx>
#include <meshSurfacePartitioner.hxx>
#include <boolList.hxx>
#include <demandDrivenData.hxx>
#include <helperFunctions.hxx>
#include <triangle.hxx>
#include <tetrahedron.hxx>
#include <labelledPoint.hxx>

#include <map>
# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshSurfaceCheckEdgeTypes::classifyEdges()
	{
		const pointFieldPMG& points = surfaceEngine_.points();
		const labelList& bp = surfaceEngine_.bp();
		const VRWGraph& pointFaces = surfaceEngine_.pointFaces();
		const edgeList& edges = surfaceEngine_.edges();
		const VRWGraph& edgeFaces = surfaceEngine_.edgeFaces();
		const labelList& facePatch = surfaceEngine_.boundaryFacePatches();
		const vectorField& fCentres = surfaceEngine_.faceCentres();

		//- check if there exist tangled parts of mesh surface where
		//- classification is not reliable
		boolList problematicPoint(pointFaces.size(), false);

		meshSurfacePartitioner mPart(surfaceEngine_);
		meshSurfaceCheckInvertedVertices checkInverted(mPart);
		const labelHashSet& invertedPoints = checkInverted.invertedVertices();
		forAllConstIter(labelHashSet, invertedPoints, it)
			problematicPoint[bp[it.key()]] = true;

		//- classify edges
		edgeTypes_.setSize(edges.size());

# ifdef USE_OMP
		label nThreads = 3 * omp_get_num_procs();
		if (edges.size() < 1000)
			nThreads = 1;
# endif

# ifdef USE_OMP
# pragma omp parallel num_threads(nThreads)
# endif
		{
# ifdef USE_OMP
# pragma omp for schedule(static, 1)
# endif
			forAll(edgeTypes_, edgeI)
				edgeTypes_[edgeI] = NONE;

			// TODO: this is not valid for non-manifold meshes
			//- start checking feature edges
# ifdef USE_OMP
# pragma omp for schedule(static, 1)
# endif
			forAll(edgeFaces, edgeI)
			{
				if (edgeFaces.sizeOfRow(edgeI) == 2)
				{
					const label f0 = edgeFaces(edgeI, 0);
					const label f1 = edgeFaces(edgeI, 1);

					if (facePatch[f0] == facePatch[f1])
						edgeTypes_[edgeI] |= PATCHEDGE;

					const edge e = edges[edgeI];

					//- check if the surface is tangled there
					if (problematicPoint[bp[e.start()]])
					{
						edgeTypes_[edgeI] |= UNDETERMINED;
						continue;
					}

					if (problematicPoint[bp[e.end()]])
					{
						edgeTypes_[edgeI] |= UNDETERMINED;
						continue;
					}

					//- check the volumes pof tets which can be formed at the edge
					const tetrahedron<point, point> tet0
					(
						points[e.start()],
						points[e.end()],
						fCentres[f0],
						fCentres[f1]
					);

					if (tet0.mag() > -VSMALL)
					{
						edgeTypes_[edgeI] |= CONCAVEEDGE;
						continue;
					}

					const tetrahedron<point, point> tet1
					(
						points[e.end()],
						points[e.start()],
						fCentres[f1],
						fCentres[f0]
					);

					if (tet1.mag() > -VSMALL)
					{
						edgeTypes_[edgeI] |= CONCAVEEDGE;
						continue;
					}

					edgeTypes_[edgeI] |= CONVEXEDGE;
				}
			}
		}

		if (Pstream::parRun())
		{
			//- check if the edge at processor boundaries are concave or convex
			const labelList& globalEdgeLabel =
				surfaceEngine_.globalBoundaryEdgeLabel();
			const Map<label>& otherProc = surfaceEngine_.otherEdgeFaceAtProc();
			const Map<label>& otherPatch = surfaceEngine_.otherEdgeFacePatch();
			const Map<label>& globalToLocalEdge =
				surfaceEngine_.globalToLocalBndEdgeAddressing();

			std::map<label, LongList<labelledPoint> > exchangeFaceCentres;
			forAll(surfaceEngine_.beNeiProcs(), i)
			{
				const label neiProc = surfaceEngine_.beNeiProcs()[i];

				exchangeFaceCentres.insert
				(
					std::make_pair(neiProc, LongList<labelledPoint>())
				);
			}

			forAllConstIter(Map<label>, otherPatch, eIter)
			{
				if (eIter() == facePatch[edgeFaces(eIter.key(), 0)])
					continue;

				const edge& e = edges[eIter.key()];
				if
					(
						problematicPoint[bp[e.start()]] ||
						problematicPoint[bp[e.end()]]
						)
				{
					edgeTypes_[eIter.key()] |= UNDETERMINED;
					continue;
				}

				const label neiProcs = otherProc[eIter.key()];
				exchangeFaceCentres[neiProcs].append
				(
					labelledPoint
					(
						globalEdgeLabel[eIter.key()],
						fCentres[edgeFaces(eIter.key(), 0)]
					)
				);
			}

			LongList<labelledPoint> receiveCentres;
			help::exchangeMap(exchangeFaceCentres, receiveCentres);

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 20)
# endif
			forAll(receiveCentres, i)
			{
				const labelledPoint& lp = receiveCentres[i];
				const label edgeI = globalToLocalEdge[lp.pointLabel()];

				// TODO: this is valid for manifold meshes, only
				if (edgeFaces.sizeOfRow(edgeI) != 1)
					continue;

				const vector fCentre = lp.coordinates();

				const edge& e = edges[edgeI];
				const label f0 = edgeFaces(edgeI, 0);

				//- check the volumes pof tets
				//- which can be formed at the edge
				tetrahedron<point, point> tet0
				(
					points[e.start()],
					points[e.end()],
					fCentres[f0],
					fCentre
				);

				if (tet0.mag() > -VSMALL)
				{
					edgeTypes_[edgeI] |= CONCAVEEDGE;
					continue;
				}

				tetrahedron<point, point> tet1
				(
					points[e.end()],
					points[e.start()],
					fCentre,
					fCentres[f0]
				);

				if (tet1.mag() > -VSMALL)
				{
					edgeTypes_[edgeI] |= CONCAVEEDGE;
					continue;
				}

				edgeTypes_[edgeI] |= CONVEXEDGE;
			}
		}

# ifdef DEBUGClassifyEdges
		polyMeshGen& mesh_ = const_cast<polyMeshGen&>(surfaceEngine_.mesh());
		const label badVertices = mesh_.addPointSubset("invertedVertices");
		forAll(problematicPoint, bpI)
			if (problematicPoint[bpI])
				mesh_.addPointToSubset
				(
					badVertices,
					surfaceEngine_.boundaryPoints()[bpI]
				);

		forAll(edgeTypes_, edgeI)
		{
			if (edgeTypes_[edgeI] & CONVEXEDGE)
			{
				Info << "Edge " << edgeI << " is convex" << endl;
			}
			else if (edgeTypes_[edgeI] & CONCAVEEDGE)
			{
				Info << "Edge " << edgeI << " is concave" << endl;
			}
			else if (edgeTypes_[edgeI] & UNDETERMINED)
			{
				Info << "Edge " << edgeI << " is not determined" << endl;
			}
			else if (edgeTypes_[edgeI] & PATCHEDGE)
			{
				Info << "Edge " << edgeI << " is a patch edge" << endl;
			}
			else
			{
				Info << "Drekec spekec" << edgeI << endl;
			}
		}
# endif
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	meshSurfaceCheckEdgeTypes::meshSurfaceCheckEdgeTypes
	(
		const meshSurfaceEngine& mse
	)
		:
		surfaceEngine_(mse),
		edgeTypes_()
	{
		classifyEdges();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshSurfaceCheckEdgeTypes::~meshSurfaceCheckEdgeTypes()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshSurfaceCheckEdgeTypes::convexEdges(labelLongList& convexEdges) const
	{
		convexEdges.clear();

		forAll(edgeTypes_, eI)
		{
			if (edgeTypes_[eI] & CONVEXEDGE)
				convexEdges.append(eI);
		}
	}

	void meshSurfaceCheckEdgeTypes::concaveEdges(labelLongList& concaveEdges) const
	{
		concaveEdges.clear();

		forAll(edgeTypes_, eI)
		{
			if (edgeTypes_[eI] & CONCAVEEDGE)
				concaveEdges.append(eI);
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //