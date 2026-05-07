#include <Aft2d_Node.hxx>

Standard_Boolean 
tnbLib::legLib::Aft2d_Node::IsInterior() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::legLib::Aft2d_Node::IsBoundary() const
{
	return Standard_False;
}