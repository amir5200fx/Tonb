#include <Dir3d.hxx>

#include <Pnt3d.hxx>

const tnbLib::Dir3d tnbLib::Dir3d::null(1.0, 0, 0);

tnbLib::Dir3d::Dir3d
(
	const Pnt3d & theP0,
	const Pnt3d & theP1
)
{
	auto v = theP1 - theP0;
	*this = Dir3d(v.XYZ());
}