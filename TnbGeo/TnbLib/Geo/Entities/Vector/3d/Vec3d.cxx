#include <Vec3d.hxx>

#include <Dir3d.hxx>

const tnbLib::Vec3d tnbLib::Vec3d::null(1.0, 0, 0);

tnbLib::Vec3d::Vec3d
(
	const Dir3d & V
)
	: gp_Vec(V.XYZ())
{
	// empty body
}