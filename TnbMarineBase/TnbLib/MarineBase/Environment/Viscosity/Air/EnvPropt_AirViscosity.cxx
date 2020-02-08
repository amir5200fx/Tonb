#include <EnvPropt_AirViscosity.hxx>

tnbLib::marineLib::AirViscosity::AirViscosity()
	: Viscosity("viscosity of air", 1.81E-5)
{
}

tnbLib::marineLib::AirViscosity::AirViscosity
(
	const Standard_Real theValue
)
	: Viscosity("viscosity of air", theValue)
{
}