#include <TModel_SingularEdge.hxx>

void tnbLib::TModel_SingularEdge::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<TModel_Vertex>>& theVertices
) const
{
	theVertices.push_back(Vtx());
}