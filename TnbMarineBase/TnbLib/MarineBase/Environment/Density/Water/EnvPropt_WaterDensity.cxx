#include <EnvPropt_WaterDensity.hxx>

tnbLib::marineLib::WaterDensity::WaterDensity()
	: Density("watre density", 998.0)
{
}

tnbLib::marineLib::WaterDensity::WaterDensity
(
	const Standard_Real theValue
)
	: Density("watre density", theValue)
{
}