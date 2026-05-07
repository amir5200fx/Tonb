#include <MeshBLayer2d_Node.hxx>

Standard_Boolean 
tnbLib::MeshBLayer2d_Node::IsBoundary() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::MeshBLayer2d_Node::IsInner() const
{
	return Standard_False;
}