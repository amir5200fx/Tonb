#include <polyMeshGenAddressing.hxx>

#include <VRWGraphSMPModifier.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcCellCells() const
	{
		if (ccPtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcCellCells() const")
				<< "cellCells already calculated"
				<< abort(FatalError);
		}
		else
		{
			const cellListPMG& cells = mesh_.cells();

			const labelList& own = mesh_.owner();
			const labelList& nei = mesh_.neighbour();

			//- create the storage
			ccPtr_ = new VRWGraph();
			VRWGraph& cellCellAddr = *ccPtr_;

			labelList nNei(cells.size());

# ifdef USE_OMP
			const label nThreads = 3 * omp_get_num_procs();
# endif

# ifdef USE_OMP
# pragma omp parallel num_threads(nThreads)
# endif
			{
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
				forAll(nNei, i)
					nNei[i] = 0;

# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
				forAll(cells, cellI)
				{
					const cell& c = cells[cellI];

					DynList<label> neiCells;

					forAll(c, fI)
					{
						label neiCell = own[c[fI]];
						if ((neiCell == cellI) && (nei[c[fI]] != -1))
							neiCell = nei[c[fI]];

						if (neiCell != cellI)
							neiCells.appendIfNotIn(neiCell);
					}

					nNei[cellI] = neiCells.size();
				}

# ifdef USE_OMP
# pragma omp barrier

# pragma omp master
# endif
				VRWGraphSMPModifier(cellCellAddr).setSizeAndRowSize(nNei);

# ifdef USE_OMP
# pragma omp barrier

				//- fill the graph with data
# pragma omp for schedule(static)
# endif
				forAll(cells, cellI)
				{
					const cell& c = cells[cellI];

					DynList<label> neiCells;

					forAll(c, fI)
					{
						label neiCell = own[c[fI]];
						if ((neiCell == cellI) && (nei[c[fI]] != -1))
							neiCell = nei[c[fI]];

						if (neiCell != cellI)
							neiCells.appendIfNotIn(neiCell);
					}

					cellCellAddr.setRow(cellI, neiCells);
				}
			}
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const VRWGraph& polyMeshGenAddressing::cellCells() const
	{
		if (!ccPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const VRWGraph& polyMeshGenAddressing::cellCells() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcCellCells();
		}

		return *ccPtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //