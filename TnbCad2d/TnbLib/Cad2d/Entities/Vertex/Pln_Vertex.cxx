#include <Pln_Vertex.hxx>

#include <Pln_Ring.hxx>

Standard_Boolean tnbLib::Pln_Vertex::IsRingPoint() const
{
	if (NbEdges() NOT_EQUAL 1) return Standard_False;

	std::vector<std::weak_ptr<Pln_Edge>> edges;
	RetrieveEdgesTo(edges);

	if (std::dynamic_pointer_cast<Pln_Ring>(edges[0].lock()))
	{
		return Standard_True;
	}
	return Standard_False;
}

Standard_Boolean tnbLib::Pln_Vertex::IsManifold() const
{
	if (IsRingPoint()) return Standard_True;
	else if (NbEdges() IS_EQUAL 2) return Standard_True;
	return Standard_False;
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::Pln_Vertex::Copy() const
{
	auto copy = std::make_shared<Pln_Vertex>(Index(), Name(), Coord());
	return std::move(copy);
}

void tnbLib::Pln_Vertex::RetrieveEdgesTo
(
	std::vector<std::weak_ptr<Pln_Edge>>& theEdges
) const
{
	theEdges.reserve(Edges().size());
	for (const auto& x : Edges())
	{
		theEdges.push_back(x.second);
	}
}