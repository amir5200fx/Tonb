#include <Entity_Connectivity.hxx>

#include <iostream>

std::vector<tnbLib::connectivity::dual>
tnbLib::dualConnectivityList
(
	const Standard_Integer theNbEdges
)
{
	std::vector<connectivity::dual> Edges(theNbEdges);
	Standard_Integer K = 0;
	for (auto& x : Edges)
	{
		x.Value(0) = K * 2 + 1;
		x.Value(1) = K * 2 + 2;

		++K;
	}
	return std::move(Edges);
}

std::vector<tnbLib::connectivity::dual>
tnbLib::dualConnectivityList_Chain
(
	const Standard_Integer theNbEdges,
	const Standard_Boolean IsClosed
)
{
	std::vector<connectivity::dual> Edges(theNbEdges);
	Standard_Integer K = 0;
	for (auto& x : Edges)
	{
		x.Value(0) = K + 1;
		x.Value(1) = K + 2;

		++K;
	}

	if (IsClosed)
	{
		Edges[Edges.size() - 1].Value(1) = 1;
	}

	return std::move(Edges);
}