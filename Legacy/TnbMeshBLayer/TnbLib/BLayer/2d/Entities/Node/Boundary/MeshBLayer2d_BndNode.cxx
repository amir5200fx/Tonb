#include <MeshBLayer2d_BndNode.hxx>

Standard_Boolean 
tnbLib::MeshBLayer2d_BndNode::IsSegment() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::MeshBLayer2d_BndNode::IsCorner() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::MeshBLayer2d_BndNode::IsBoundary() const
{
	return Standard_True;
}