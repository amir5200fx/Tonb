#include <HydStatic_HydCurve.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

tnbLib::HydStatic_HydCurve::HydStatic_HydCurve
(
	Handle(Geom2d_Curve) && theCurve
)
	: theGeom_(std::move(theCurve))
{
	//- empty body
}

tnbLib::HydStatic_HydCurve::HydStatic_HydCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: theGeom_(theCurve)
{
	//- empty body
}

tnbLib::HydStatic_HydCurve::HydStatic_HydCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	Handle(Geom2d_Curve)&& theCurve
)
	: HydStatic_Entity(theIndex, theName)
	, theGeom_(std::move(theCurve))
{
	//- empty body
}

tnbLib::HydStatic_HydCurve::HydStatic_HydCurve
(
	const Standard_Integer theIndex,
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_Entity(theIndex, theName)
	, theGeom_(theCurve)
{
	//- empty body
}

tnbLib::Pnt2d 
tnbLib::HydStatic_HydCurve::FirstCoord() const
{
	Debug_Null_Pointer(Geometry());
	const auto& g = *Geometry();
	auto p = g.Value(g.FirstParameter());
	return std::move(p);
}

tnbLib::Pnt2d 
tnbLib::HydStatic_HydCurve::LastCoord() const
{
	Debug_Null_Pointer(Geometry());
	const auto& g = *Geometry();
	auto p = g.Value(g.LastParameter());
	return std::move(p);
}