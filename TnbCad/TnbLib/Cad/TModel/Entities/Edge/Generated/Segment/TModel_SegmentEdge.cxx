#include <TModel_SegmentEdge.hxx>

std::vector<std::shared_ptr<tnbLib::TModel_Vertex>> 
tnbLib::TModel_SegmentEdge::RetrieveVertices() const
{
	std::vector<std::shared_ptr<TModel_Vertex>> vertices;
	vertices.reserve(2);
	RetrieveVerticesTo(vertices);
	return std::move(vertices);
}

void tnbLib::TModel_SegmentEdge::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<TModel_Vertex>>& theVertices
) const
{
	theVertices.push_back(Vtx0());
	theVertices.push_back(Vtx1());
}