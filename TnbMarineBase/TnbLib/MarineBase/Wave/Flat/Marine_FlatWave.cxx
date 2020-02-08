#include <Marine_FlatWave.hxx>

#include <Cad2d_GeoSketch_LineSegment.hxx>
#include <Pln_Tools.hxx>

void tnbLib::Marine_FlatWave::MakeProfileCurve
(
	const Pnt2d& x0,
	const Pnt2d& x1
)
{
	auto sketch =
		std::make_shared<Cad2d_GeoSketch_LineSegment>(x0, x1);
	Debug_Null_Pointer(sketch);

	ChangeCurveGeometry() = Pln_Tools::ConvertToBSpline(sketch->Geometry());
}