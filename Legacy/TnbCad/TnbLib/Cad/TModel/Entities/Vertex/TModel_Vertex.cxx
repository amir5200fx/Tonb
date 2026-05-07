#include <TModel_Vertex.hxx>

Standard_Boolean 
tnbLib::TModel_Vertex::IsOrphan() const
{
	return NOT NbEdges();
}