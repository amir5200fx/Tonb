#include <EnvPropt_WaterViscosity.hxx>

tnbLib::marineLib::WaterViscosity::WaterViscosity()
	: Viscosity("viscosity of water", 8.9E-4)
{
}

tnbLib::marineLib::WaterViscosity::WaterViscosity
(
	const Standard_Real theValue
)
	: Viscosity("viscosity of water", theValue)
{
}