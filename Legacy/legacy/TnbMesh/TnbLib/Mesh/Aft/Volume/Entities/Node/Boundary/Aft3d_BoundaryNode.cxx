#include <Aft3d_BoundaryNode.hxx>

Standard_Boolean 
tnbLib::legLib::Aft3d_BoundaryNode::IsCorner() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_BoundaryNode::IsSegment() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_BoundaryNode::IsFace() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_BoundaryNode::IsBoundary() const
{
	return Standard_True;
}