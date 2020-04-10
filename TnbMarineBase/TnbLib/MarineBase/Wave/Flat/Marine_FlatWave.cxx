#include <Marine_FlatWave.hxx>

#include <GeoSketch2d_Segment.hxx>
#include <Pln_Tools.hxx>

tnbLib::Dir3d 
tnbLib::Marine_FlatWave::SurfaceDirection() const
{
	return Dir3d(Origin().XDirection().XYZ());
}

void tnbLib::Marine_FlatWave::MakeProfileCurve
(
	const Pnt2d& x0,
	const Pnt2d& x1
)
{
	auto sketch =
		std::make_shared<GeoSketch2d_Segment>(x0, x1);
	Debug_Null_Pointer(sketch);

	ChangeCurveGeometry() = Pln_Tools::ConvertToBSpline(sketch->Geometry());
}