#include <meshSurfaceEdgeExtractorFUN.hxx>

#include <demandDrivenData.hxx>
#include <meshOctree.hxx>
#include <triSurf.hxx>
#include <meshSurfaceEngine.hxx>
#include <meshSurfaceMapper.hxx>
#include <helperFunctions.hxx>
#include <createFundamentalSheetsJFS.hxx>
#include <meshSurfaceOptimizer.hxx>
#include <meshSurfaceCheckEdgeTypes.hxx>
#include <meshSurfaceEngine.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

//#define DEBUGMapping

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshSurfaceEdgeExtractorFUN::distributeBoundaryFaces()
	{
		meshSurfaceEngine mse(mesh_);

		const faceList::subList& bFaces = mse.boundaryFaces();
		const labelList& faceOwner = mse.faceOwners();
		const pointFieldPMG& points = mse.points();

		//- set size of patchNames, newBoundaryFaces_ and newBoundaryOwners_
		const triSurf& surface = meshOctree_.surface();
		const label nPatches = surface.patches().size();

		wordList patchNames(nPatches);
		VRWGraph newBoundaryFaces;
		labelLongList newBoundaryOwners(bFaces.size());
		labelLongList newBoundaryPatches(bFaces.size());

		//- set patchNames
		forAll(surface.patches(), patchI)
			patchNames[patchI] = surface.patches()[patchI].name();

		//- append boundary faces
		forAll(bFaces, bfI)
		{
			newBoundaryFaces.appendList(bFaces[bfI]);
			newBoundaryOwners[bfI] = faceOwner[bfI];
		}

		//- find the region for face by finding the patch nearest
		//- to the face centre
# ifdef USE_OMP
# pragma omp parallel for if( bFaces.size() > 100 ) schedule(guided)
# endif
		forAll(bFaces, bfI)
		{
			const point c = bFaces[bfI].centre(points);

			label facePatch, nt;
			point p;
			scalar distSq;

			meshOctree_.findNearestSurfacePoint(p, distSq, nt, facePatch, c);

			if ((facePatch > -1) && (facePatch < nPatches))
			{
				newBoundaryPatches[bfI] = facePatch;
			}
			else
			{
				FatalErrorIn
				(
					"void meshSurfaceEdgeExtractorNonTopo::"
					"distributeBoundaryFaces()"
				) << "Cannot distribute a face " << bFaces[bfI] << " into any "
					<< "surface patch!. Exiting.." << exit(FatalError);
			}
		}

		polyMeshGenModifier(mesh_).replaceBoundary
		(
			patchNames,
			newBoundaryFaces,
			newBoundaryOwners,
			newBoundaryPatches
		);
	}

	void meshSurfaceEdgeExtractorFUN::reviseCorners()
	{

	}

	void meshSurfaceEdgeExtractorFUN::reviseEdges()
	{

	}

	void meshSurfaceEdgeExtractorFUN::remapBoundaryPoints()
	{
		meshSurfaceEngine& mse = surfaceEngine();
		meshSurfaceMapper mapper(mse, meshOctree_);

		mapper.mapVerticesOntoSurfacePatches();
	}

	void meshSurfaceEdgeExtractorFUN::createBasicFundamentalSheets()
	{
		createFundamentalSheetsJFS edgeSheets(mesh_, createWrapperSheet_);

		clearOut();
	}

	void meshSurfaceEdgeExtractorFUN::smoothMeshSurface()
	{
		meshSurfaceEngine& mse = surfaceEngine();

		meshSurfaceOptimizer mso(mse, meshOctree_);
		mso.optimizeSurface();
	}

	void meshSurfaceEdgeExtractorFUN::improveQualityOfFundamentalSheets()
	{
		const meshSurfaceEngine& mse = surfaceEngine();
		const edgeList& edges = mse.edges();

		meshSurfaceCheckEdgeTypes edgeCheck(mse);

		label id = mesh_.addPointSubset("convexEdges");
		labelLongList helper;
		edgeCheck.convexEdges(helper);
		forAll(helper, i)
		{
			mesh_.addPointToSubset(id, edges[helper[i]].start());
			mesh_.addPointToSubset(id, edges[helper[i]].end());
		}

		id = mesh_.addPointSubset("concaveEdges");
		edgeCheck.concaveEdges(helper);
		forAll(helper, i)
		{
			mesh_.addPointToSubset(id, edges[helper[i]].start());
			mesh_.addPointToSubset(id, edges[helper[i]].end());
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //