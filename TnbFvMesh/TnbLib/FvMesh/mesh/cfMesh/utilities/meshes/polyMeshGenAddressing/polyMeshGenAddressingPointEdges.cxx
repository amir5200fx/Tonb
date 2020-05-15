#include <polyMeshGenAddressing.hxx>

#include <VRWGraphSMPModifier.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void polyMeshGenAddressing::calcPointEdges() const
	{
		if (pePtr_)
		{
			FatalErrorIn("polyMeshGenAddressing::calcPointEdges() const")
				<< "pointEdges already calculated"
				<< abort(FatalError);
		}
		else
		{
			const edgeList& e = edges();

			//- create the addressing
			pePtr_ = new VRWGraph();
			VRWGraph& pointEdgeAddr = *pePtr_;

			VRWGraphSMPModifier(pointEdgeAddr).reverseAddressing(e);
			pointEdgeAddr.setSize(mesh_.points().size());
		}
	}

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const VRWGraph& polyMeshGenAddressing::pointEdges() const
	{
		if (!pePtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"const VRWGraph& polyMeshGenAddressing::pointEdges() const"
				) << "Calculating addressing inside a parallel region."
				<< " This is not thread safe" << exit(FatalError);
# endif

			calcPointEdges();
		}

		return *pePtr_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //