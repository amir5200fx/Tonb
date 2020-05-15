#include <polyMeshGenAddressing.hxx>

#include <VRWGraphSMPModifier.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcPointPoints() const
	{
		if (ppPtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcPointPoints() const")
				<< "pointPoints already calculated"
				<< abort(FatalError);
		}
		else
		{
			ppPtr_ = new VRWGraph();
			VRWGraph& pp = *ppPtr_;

			const faceListPMG& faces = mesh_.faces();
			const VRWGraph& pointFaces = this->pointFaces();

			labelList nPoints(pointFaces.size());

# ifdef USE_OMP
			const label nThreads = 3 * omp_get_num_procs();
# pragma omp parallel num_threads(nThreads) if( nPoints.size() > 10000 )
# endif
			{
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
				forAll(nPoints, i)
					nPoints[i] = 0;

# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
				forAll(pointFaces, pointI)
				{
					DynList<label, 32> helper;

					forAllRow(pointFaces, pointI, pfI)
					{
						const face& f = faces[pointFaces(pointI, pfI)];

						const label pos = f.which(pointI);
						helper.appendIfNotIn(f.prevLabel(pos));
						helper.appendIfNotIn(f.nextLabel(pos));
					}

					nPoints[pointI] = helper.size();
				}

# ifdef USE_OMP
# pragma omp barrier

# pragma omp master
# endif
				VRWGraphSMPModifier(pp).setSizeAndRowSize(nPoints);

# ifdef USE_OMP
# pragma omp barrier

# pragma omp for schedule(static)
# endif
				forAll(pointFaces, pointI)
				{
					DynList<label, 32> helper;

					forAllRow(pointFaces, pointI, pfI)
					{
						const face& f = faces[pointFaces(pointI, pfI)];

						const label pos = f.which(pointI);
						const label pLabel = f.prevLabel(pos);
						const label nLabel = f.nextLabel(pos);

						helper.appendIfNotIn(nLabel);
						helper.appendIfNotIn(pLabel);
					}

					pp.setRow(pointI, helper);
				}
			}
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const VRWGraph& polyMeshGenAddressing::pointPoints() const
	{
		if (!ppPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const VRWGraph& polyMeshGenAddressing::pointPoints() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcPointPoints();
		}

		return *ppPtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //