#include <polyMeshGenAddressing.hxx>

#include <VRWGraphSMPModifier.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcPointCells() const
	{
		if (pcPtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcPointCells() const")
				<< "pointCells already calculated"
				<< abort(FatalError);
		}
		else
		{
			const VRWGraph& cellPoints = this->cellPoints();

			//- create the storage
			pcPtr_ = new VRWGraph();
			VRWGraph& pointCellAddr = *pcPtr_;

			VRWGraphSMPModifier(pointCellAddr).reverseAddressing(cellPoints);
			pointCellAddr.setSize(mesh_.points().size());
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const VRWGraph& polyMeshGenAddressing::pointCells() const
	{
		if (!pcPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const VRWGraph& polyMeshGenAddressing::pointCells() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcPointCells();
		}

		return *pcPtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //