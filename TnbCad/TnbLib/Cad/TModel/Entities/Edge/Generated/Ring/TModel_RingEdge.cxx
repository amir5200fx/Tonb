#include <TModel_RingEdge.hxx>

std::vector<std::shared_ptr<tnbLib::TModel_Vertex>> 
tnbLib::TModel_RingEdge::RetrieveVertices() const
{
	std::vector<std::shared_ptr<TModel_Vertex>> vertices;
	vertices.reserve(1);
	RetrieveVerticesTo(vertices);
	return std::move(vertices);
}

void tnbLib::TModel_RingEdge::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<TModel_Vertex>>& theVertices
) const
{
	theVertices.push_back(Vtx());
}