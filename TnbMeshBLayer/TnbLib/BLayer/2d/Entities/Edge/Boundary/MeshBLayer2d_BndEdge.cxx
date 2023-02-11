#include <MeshBLayer2d_BndEdge.hxx>

Standard_Boolean 
tnbLib::MeshBLayer2d_BndEdge::IsSegment() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::MeshBLayer2d_BndEdge::IsBoundary() const
{
	return Standard_True;
}