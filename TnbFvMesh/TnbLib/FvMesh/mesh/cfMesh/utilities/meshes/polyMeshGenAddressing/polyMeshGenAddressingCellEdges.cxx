#include <polyMeshGenAddressing.hxx>

#include <DynList.hxx>
#include <VRWGraphSMPModifier.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcCellEdges() const
	{
		if (cePtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcCellEdges() const")
				<< "cellEdges already calculated"
				<< abort(FatalError);
		}
		else
		{
			const cellListPMG& cells = mesh_.cells();
			const VRWGraph& fe = faceEdges();

			cePtr_ = new VRWGraph();
			VRWGraph& cellEdgeAddr = *cePtr_;

			labelList nEdges(cells.size());

# ifdef USE_OMP
			const label nThreads = 3 * omp_get_num_procs();
# endif

# ifdef USE_OMP
# pragma omp parallel num_threads(nThreads) if( cells.size() > 10000 )
# endif
			{
# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
				forAll(nEdges, i)
					nEdges[i] = 0;

# ifdef USE_OMP
# pragma omp for schedule(static)
# endif
				forAll(cells, cellI)
				{
					const cell& c = cells[cellI];

					DynList<label, 32> cEdges;

					forAll(c, fI)
					{
						const label faceI = c[fI];

						forAllRow(fe, faceI, eI)
							cEdges.appendIfNotIn(fe(faceI, eI));
					}

					nEdges[cellI] = cEdges.size();
				}

# ifdef USE_OMP
# pragma omp barrier

# pragma omp master
# endif
				VRWGraphSMPModifier(cellEdgeAddr).setSizeAndRowSize(nEdges);

# ifdef USE_OMP
# pragma omp barrier

# pragma omp for schedule(static)
# endif
				forAll(cells, cellI)
				{
					const cell& c = cells[cellI];

					DynList<label, 32> cEdges;

					forAll(c, fI)
					{
						const label faceI = c[fI];

						forAllRow(fe, faceI, eI)
							cEdges.appendIfNotIn(fe(faceI, eI));
					}

					cellEdgeAddr.setRow(cellI, cEdges);
				}
			}
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const VRWGraph& polyMeshGenAddressing::cellEdges() const
	{
		if (!cePtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const VRWGraph& polyMeshGenAddressing::cellEdges() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcCellEdges();
		}

		return *cePtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //