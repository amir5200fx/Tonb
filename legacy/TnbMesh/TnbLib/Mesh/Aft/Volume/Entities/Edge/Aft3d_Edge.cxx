#include <Aft3d_Edge.hxx>

Standard_Boolean 
tnbLib::legLib::Aft3d_Edge::IsInterior() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_Edge::IsBoundary() const
{
	return Standard_True;
}