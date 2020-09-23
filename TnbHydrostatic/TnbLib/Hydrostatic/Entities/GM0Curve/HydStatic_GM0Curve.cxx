#include <HydStatic_GM0Curve.hxx>

#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

tnbLib::HydStatic_GM0Curve::HydStatic_GM0Curve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theCurve)
{
}

tnbLib::HydStatic_GM0Curve::HydStatic_GM0Curve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_GM0Curve::HydStatic_GM0Curve
(
	const Standard_Integer theIndex,
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_HydCurve(theIndex, theName, theCurve)
{
}

Standard_Real 
tnbLib::HydStatic_GM0Curve::GM0() const
{
	Debug_Null_Pointer(Geometry());
	const auto& geom = *Geometry();

	const auto v = geom.Value(geom.LastParameter());
	return v.Y();
}