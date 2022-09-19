#include <Geo2d_TriangleQualityTools.hxx>

#include <Pnt2d.hxx>

#include <../Burkardt/Burkardt.h>

Standard_Real 
tnbLib::Geo2d_TriangleQualityTools::Vlrms2Ratio
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1,
	const Pnt2d & theP2
)
{
	Standard_Real xy[6];

	xy[0] = theP0.X();
	xy[1] = theP0.Y();
	xy[2] = theP1.X();
	xy[3] = theP1.Y();
	xy[4] = theP2.X();
	xy[5] = theP2.Y();

	return triangle_quality_2d(xy);
}