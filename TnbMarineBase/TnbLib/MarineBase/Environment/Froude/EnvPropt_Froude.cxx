#include <EnvPropt_Froude.hxx>

tnbLib::marineLib::Froude::Froude(const Standard_Real theValue)
	: realParam("froude number", dimless, theValue)
{
}