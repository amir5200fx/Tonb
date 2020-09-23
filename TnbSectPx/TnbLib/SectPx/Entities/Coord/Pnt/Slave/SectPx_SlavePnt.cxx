#include <SectPx_SlavePnt.hxx>

Standard_Boolean 
tnbLib::SectPx_SlavePnt::IsEmpty() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_SlavePnt::IsSlave() const
{
	return Standard_True;
}