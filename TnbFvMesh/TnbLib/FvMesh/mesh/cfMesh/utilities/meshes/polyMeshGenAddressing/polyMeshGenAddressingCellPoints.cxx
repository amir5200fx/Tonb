#include <polyMeshGenAddressing.hxx>

#include <VRWGraphSMPModifier.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcCellPoints() const
	{
		if (cpPtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcCellPoints() const")
				<< "cellPoints already calculated"
				<< abort(FatalError);
		}
		else
		{
			const cellListPMG& cells = mesh_.cells();
			const faceListPMG& faces = mesh_.faces();

			//- create the storage
			cpPtr_ = new VRWGraph(cells.size());
			VRWGraph& cellPointsAddr = *cpPtr_;

			labelList nPoints(cells.size());

# ifdef USE_OMP
			const label nThreads = 3 * omp_get_num_procs();
# pragma omp parallel num_threads(nThreads) if( cells.size() > 10000 )
# endif
			{
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
				forAll(nPoints, i)
					nPoints[i] = i;

# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
				forAll(cells, cellI)
				{
					const cell& c = cells[cellI];

					DynList<label, 32> cPoints;
					forAll(c, fI)
					{
						const face& f = faces[c[fI]];

						forAll(f, pI)
							cPoints.appendIfNotIn(f[pI]);
					}

					nPoints[cellI] = cPoints.size();
				}

# ifdef USE_OMP
# pragma omp barrier

# pragma omp master
# endif
				VRWGraphSMPModifier(cellPointsAddr).setSizeAndRowSize(nPoints);

# ifdef USE_OMP
# pragma omp barrier

# pragma omp for schedule(static)
# endif
				forAll(cells, cellI)
				{
					const cell& c = cells[cellI];

					DynList<label, 32> cPoints;
					forAll(c, fI)
					{
						const face& f = faces[c[fI]];

						forAll(f, pI)
							cPoints.appendIfNotIn(f[pI]);
					}

					cellPointsAddr.setRow(cellI, cPoints);
				}
			}
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const VRWGraph& polyMeshGenAddressing::cellPoints() const
	{
		if (!cpPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const VRWGraph& polyMeshGenAddressing::cellPoints() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcCellPoints();
		}

		return *cpPtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //