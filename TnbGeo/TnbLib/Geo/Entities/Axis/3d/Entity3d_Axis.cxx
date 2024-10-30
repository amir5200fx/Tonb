#include <Entity3d_Axis.hxx>

#include <Pnt3d.hxx>
#include <Dir3d.hxx>

gp_Ax2 tnbLib::make_ax2(const Pnt3d& c, const Dir3d& n, const Dir3d& vx)
{
	return { c, n, vx };
}

gp_Ax2 tnbLib::make_ax2(const Pnt3d& c, const Dir3d& v)
{
	return { c,v };
}
