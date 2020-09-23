#include <GeoSketch2d_Ellipse.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Precision.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>

tnbLib::GeoSketch2d_Ellipse::GeoSketch2d_Ellipse
(
	const gp_Ax2d & theAxis, 
	const Standard_Real theMajorRadius, 
	const Standard_Real theMinorRadius,
	const Standard_Boolean theSense
)
{
	if (theMajorRadius < theMinorRadius)
	{
		FatalErrorIn("GeoSketch2d_Ellipse::GeoSketch2d_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	if (theMinorRadius < Precision::Confusion())
	{
		FatalErrorIn("GeoSketch2d_Ellipse::GeoSketch2d_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) geom =
		new Geom2d_Ellipse(theAxis, theMajorRadius, theMinorRadius, theSense);

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			geom, geom->FirstParameter(),
			geom->LastParameter());
}

tnbLib::GeoSketch2d_Ellipse::GeoSketch2d_Ellipse
(
	const gp_Ax22d & theAxis,
	const Standard_Real theMajorRadius,
	const Standard_Real theMinorRadius
)
{
	if (theMajorRadius < theMinorRadius)
	{
		FatalErrorIn("GeoSketch2d_Ellipse::GeoSketch2d_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	if (theMinorRadius < Precision::Confusion())
	{
		FatalErrorIn("GeoSketch2d_Ellipse::GeoSketch2d_Ellipse()")
			<< "Invalid Data: " << endl
			<< " - major radius: " << theMajorRadius << endl
			<< " - minor radius: " << theMinorRadius << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) geom =
		new Geom2d_Ellipse(theAxis, theMajorRadius, theMinorRadius);

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			geom, geom->FirstParameter(),
			geom->LastParameter());
}