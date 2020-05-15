#include <polyMeshGenAddressing.hxx>

#include <VRWGraphSMPModifier.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcFaceEdges() const
	{
		if (fePtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcFaceEdges() const")
				<< "faceEdges already calculated"
				<< abort(FatalError);
		}
		else
		{
			fePtr_ = new VRWGraph();
			VRWGraph& faceEdgesAddr = *fePtr_;

			const edgeList& edges = this->edges();

			const VRWGraph& pointFaces = this->pointFaces();
			const faceListPMG& faces = mesh_.faces();

			labelList nfe(faces.size());

# ifdef USE_OMP
			const label nThreads = 3 * omp_get_num_procs();
# endif

# ifdef USE_OMP
# pragma omp parallel num_threads(nThreads) if( faces.size() > 10000 )
# endif
			{
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
				forAll(faces, faceI)
					nfe[faceI] = faces[faceI].size();

# ifdef USE_OMP
# pragma omp barrier

# pragma omp master
# endif
				VRWGraphSMPModifier(faceEdgesAddr).setSizeAndRowSize(nfe);

# ifdef USE_OMP
# pragma omp barrier

# pragma omp for schedule(static)
# endif
				forAll(edges, edgeI)
				{
					const edge ee = edges[edgeI];
					const label s = ee.start();

					forAllRow(pointFaces, s, pfI)
					{
						const label faceI = pointFaces(s, pfI);

						const face& f = faces[faceI];
						forAll(f, eI)
						{
							if (f.faceEdge(eI) == ee)
							{
								faceEdgesAddr[faceI][eI] = edgeI;
								break;
							}
						}
					}
				}
			}
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const VRWGraph& polyMeshGenAddressing::faceEdges() const
	{
		if (!fePtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const VRWGraph& polyMeshGenAddressing::faceEdges() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcFaceEdges();
		}

		return *fePtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //