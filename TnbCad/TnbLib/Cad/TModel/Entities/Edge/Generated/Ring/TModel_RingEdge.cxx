#include <TModel_RingEdge.hxx>

void tnbLib::TModel_RingEdge::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<TModel_Vertex>>& theVertices
) const
{
	theVertices.push_back(Vtx());
}