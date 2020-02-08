#include <EnvPropt_Gravity.hxx>

tnbLib::marineLib::Gravity::Gravity()
	: vec3Param("gravity", dimAcceleration, Vec3d(0, 0, -9.806))
{
}

tnbLib::marineLib::Gravity::Gravity(const Vec3d & theValue)
	: vec3Param("gravity", dimAcceleration, theValue)
{
}