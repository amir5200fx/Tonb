#include <EnvPropt_Velocity.hxx>

tnbLib::marineLib::Velocity::Velocity
(
	const Standard_Real theValue
)
	: realParam("velocity", dimVelocity, theValue)
{
}