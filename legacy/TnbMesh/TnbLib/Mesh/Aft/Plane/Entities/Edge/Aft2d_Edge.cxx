#include <Aft2d_Edge.hxx>

Standard_Boolean 
tnbLib::legLib::Aft2d_Edge::IsInterior() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::legLib::Aft2d_Edge::IsBoundary() const
{
	return Standard_False;
}