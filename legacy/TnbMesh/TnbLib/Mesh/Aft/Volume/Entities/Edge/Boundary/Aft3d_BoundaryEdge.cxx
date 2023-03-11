#include <Aft3d_BoundaryEdge.hxx>

Standard_Boolean 
tnbLib::legLib::Aft3d_BoundaryEdge::IsBoundary() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_BoundaryEdge::IsSegment() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_BoundaryEdge::IsFace() const
{
	return Standard_False;
}