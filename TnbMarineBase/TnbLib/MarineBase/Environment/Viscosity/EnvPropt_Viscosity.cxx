#include <EnvPropt_Viscosity.hxx>

tnbLib::marineLib::Viscosity::Viscosity
(
	const word & theName,
	const Standard_Real theValue
)
	: realParam(theName, dimPressure* dimTime, theValue)
{
}