#include <polyMeshGenAddressing.hxx>

#include <VRWGraphSMPModifier.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcEdgeCells() const
	{
		if (ecPtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcEdgeCells() const")
				<< "edgeCells already calculated"
				<< abort(FatalError);
		}
		else
		{
			const VRWGraph& ce = cellEdges();

			ecPtr_ = new VRWGraph();
			VRWGraph& edgeCellAddr = *ecPtr_;

			VRWGraphSMPModifier(edgeCellAddr).reverseAddressing(ce);
			edgeCellAddr.setSize(edges().size());
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const VRWGraph& polyMeshGenAddressing::edgeCells() const
	{
		if (!ecPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const VRWGraph& polyMeshGenAddressing::edgeCells() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcEdgeCells();
		}

		return *ecPtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //