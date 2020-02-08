#include <EnvPropt_AirDensity.hxx>

tnbLib::marineLib::AirDensity::AirDensity()
	: Density("air density", 1.225)
{
}

tnbLib::marineLib::AirDensity::AirDensity
(
	const Standard_Real theValue
)
	: Density("air density", theValue)
{
}