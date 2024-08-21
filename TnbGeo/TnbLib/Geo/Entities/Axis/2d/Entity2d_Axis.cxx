#include <Entity2d_Axis.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>

gp_Ax2d tnbLib::make_ax2d(const Pnt2d& theCoord, const Dir2d& theDir)
{
	return gp_Ax2d(theCoord, theDir);
}
