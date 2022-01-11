#include <TModel_SegmentEdge.hxx>

void tnbLib::TModel_SegmentEdge::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<TModel_Vertex>>& theVertices
) const
{
	theVertices.push_back(Vtx0());
	theVertices.push_back(Vtx1());
}