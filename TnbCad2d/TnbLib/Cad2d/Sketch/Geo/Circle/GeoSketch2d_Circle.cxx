#include <GeoSketch2d_Circle.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Precision.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_TrimmedCurve.hxx>

tnbLib::GeoSketch2d_Circle::GeoSketch2d_Circle
(
	const gp_Ax2d & theAxis,
	const Standard_Real theRadius,
	const Standard_Boolean theSense
)
{
	if (theRadius <= Precision::Confusion())
	{
		FatalErrorIn("GeoSketch2d_Circle::GeoSketch2d_Circle()")
			<< "Invalid Radius: " << theRadius << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) circle = new Geom2d_Circle(theAxis, theRadius, theSense);

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			circle,
			circle->FirstParameter(),
			circle->LastParameter()
		);
}

tnbLib::GeoSketch2d_Circle::GeoSketch2d_Circle
(
	const gp_Ax22d & theAxis, 
	const Standard_Real theRadius
)
{
	if (theRadius <= Precision::Confusion())
	{
		FatalErrorIn("GeoSketch2d_Circle::GeoSketch2d_Circle()")
			<< "Invalid Radius: " << theRadius << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) circle = new Geom2d_Circle(theAxis, theRadius);

	ChangeGeometry() =
		new Geom2d_TrimmedCurve
		(
			circle,
			circle->FirstParameter(),
			circle->LastParameter()
		);
}