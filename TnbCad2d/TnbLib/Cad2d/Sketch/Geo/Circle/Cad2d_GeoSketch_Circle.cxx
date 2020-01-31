#include <Cad2d_GeoSketch_Circle.hxx>

#include <UnitSystem.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_TrimmedCurve.hxx>

#include <Precision.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::Cad2d_GeoSketch_Circle::Cad2d_GeoSketch_Circle
(
	const Pnt2d & theCentre, 
	const Standard_Real theRadius
)
{
	if (theRadius <= Precision::Confusion())
	{
		FatalErrorIn("Cad2d_GeoSketch_Circle()")
			<< "Invalid Radius: " << theRadius << endl
			<< abort(FatalError);
	}

	gp_Ax2d axe(theCentre, gp::DX2d());
	Handle(Geom2d_Curve) circle = new Geom2d_Circle(axe, theRadius);

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			circle,
			circle->FirstParameter(),
			circle->LastParameter()
		);
}

tnbLib::Cad2d_GeoSketch_Circle::Cad2d_GeoSketch_Circle
(
	const Pnt2d & theCentre, 
	const Standard_Real theRadius, 
	const Standard_Boolean theSense
)
{
	if (theRadius <= Precision::Confusion())
	{
		FatalErrorIn("Cad2d_GeoSketch_Circle()")
			<< "Invalid Radius: " << theRadius << endl
			<< abort(FatalError);
	}

	gp_Ax2d axe(theCentre, gp::DX2d());
	Handle(Geom2d_Curve) circle = new Geom2d_Circle(axe, theRadius);

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			circle,
			circle->FirstParameter(),
			circle->LastParameter(),
			theSense
		);
}

tnbLib::Cad2d_GeoSketch_Circle::Cad2d_GeoSketch_Circle
(
	const Pnt2d & theCentre, 
	const Standard_Real theRadius,
	const Dir2d & theDir, 
	const Standard_Real theDeg, 
	const Standard_Boolean theSense
)
{
	if (theRadius <= Precision::Confusion())
	{
		FatalErrorIn("Cad2d_GeoSketch_Circle()")
			<< "Invalid Radius: " << theRadius << endl
			<< abort(FatalError);
	}

	auto deg = ConvertUnit(UnitSystem_Angle_deg, UnitSystem_Angle_rad)*theDeg;

	auto n = (Standard_Integer)(deg / (2 * PI));
	deg = deg - n * (2 * PI);

	gp_Ax2d axe(theCentre, theDir);
	Handle(Geom2d_Curve) circle = new Geom2d_Circle(axe, theRadius);

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			circle,
			0,
			deg,
			theSense
		);
}