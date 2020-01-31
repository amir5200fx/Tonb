#include <Cad2d_GeoSketch_Ellipse.hxx>

#include <Precision.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>

#include <UnitSystem.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::Cad2d_GeoSketch_Ellipse::Cad2d_GeoSketch_Ellipse
(
	const Pnt2d & theCentre, 
	const Standard_Real theMajorRadius,
	const Standard_Real theMinorRadius,
	const Standard_Boolean theSense
)
{
	if (theMajorRadius < theMinorRadius)
	{
		FatalErrorIn("Cad2d_GeoSketch_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	if (theMinorRadius < Precision::Confusion())
	{
		FatalErrorIn("Cad2d_GeoSketch_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	auto axe = gp_Ax2d(theCentre, gp::DX2d());
	Handle(Geom2d_Curve) geom = 
		new Geom2d_Ellipse(axe, theMajorRadius, theMinorRadius, theSense);

	ChangeGeometry() = 
		new Geom2d_TrimmedCurve
		(
			geom, geom->FirstParameter(), 
			geom->LastParameter(), theSense);
}

tnbLib::Cad2d_GeoSketch_Ellipse::Cad2d_GeoSketch_Ellipse
(
	const Pnt2d & theCentre, 
	const Standard_Real theMajorRadius,
	const Standard_Real theMinorRadius,
	const Standard_Real theDeg,
	const Standard_Boolean theSense
)
{
	if (theMajorRadius < theMinorRadius)
	{
		FatalErrorIn("Cad2d_GeoSketch_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	if (theMinorRadius < Precision::Confusion())
	{
		FatalErrorIn("Cad2d_GeoSketch_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	auto axe = gp_Ax2d(theCentre, gp::DX2d());
	Handle(Geom2d_Curve) geom = new Geom2d_Ellipse(axe, theMajorRadius, theMinorRadius, theSense);

	auto deg = ConvertUnit(UnitSystem_Angle_deg, UnitSystem_Angle_rad)*theDeg;

	auto n = (Standard_Integer)(deg / (2 * PI));
	deg = deg - n * (2 * PI);

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			geom,
			0,
			deg,
			theSense
		);
}

tnbLib::Cad2d_GeoSketch_Ellipse::Cad2d_GeoSketch_Ellipse
(
	const Pnt2d & theCentre, 
	const Dir2d & theDir, 
	const Standard_Real theMajorRadius,
	const Standard_Real theMinorRadius,
	const Standard_Real theDeg, 
	const Standard_Boolean theSense
)
{
	if (theMajorRadius < theMinorRadius)
	{
		FatalErrorIn("Cad2d_GeoSketch_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	if (theMinorRadius < Precision::Confusion())
	{
		FatalErrorIn("Cad2d_GeoSketch_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	auto axe = gp_Ax2d(theCentre, theDir);
	Handle(Geom2d_Curve) geom = new Geom2d_Ellipse(axe, theMajorRadius, theMinorRadius, theSense);

	auto deg = ConvertUnit(UnitSystem_Angle_deg, UnitSystem_Angle_rad)*theDeg;

	auto n = (Standard_Integer)(deg / (2 * PI));
	deg = deg - n * (2 * PI);

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			geom,
			0,
			deg,
			theSense
		);
}