#include <EnvPropt_Density.hxx>

tnbLib::marineLib::Density::Density
(
	const word & theName,
	const Standard_Real theValue
)
	: realParam(theName, dimDensity, theValue)
{
}