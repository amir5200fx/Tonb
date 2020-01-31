#include <Cad2d_GeoSketch_LineSegment.hxx>

#include <Vec2d.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Precision.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

tnbLib::Cad2d_GeoSketch_LineSegment::Cad2d_GeoSketch_LineSegment
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	if (theP1.Distance(theP0) <= Precision::Confusion())
	{
		FatalErrorIn("Cad2d_GeoSketch_LineSegment::Cad2d_GeoSketch_LineSegment()")
			<< "Invalid Data: " << endl
			<< " - P0: " << theP0 << endl
			<< " - P1: " << theP1 << endl
			<< abort(FatalError);
	}

	Dir2d dir(Vec2d(theP0, theP1));
	Handle(Geom2d_Curve) geom = new Geom2d_Line(theP0, dir);

	Geom2dAPI_ProjectPointOnCurve proj;
	proj.Init(theP0, geom);
	auto pr0 = proj.LowerDistanceParameter();

	proj.Init(theP1, geom);
	auto pr1 = proj.LowerDistanceParameter();

	ChangeGeometry() = new Geom2d_TrimmedCurve(geom, pr0, pr1);
}

tnbLib::Cad2d_GeoSketch_LineSegment::Cad2d_GeoSketch_LineSegment
(
	const Pnt2d & theP0, 
	const Dir2d & theDir, 
	const Standard_Real theLength
)
{
	if (theLength <= Precision::Confusion())
	{
		FatalErrorIn("Cad2d_GeoSketch_LineSegment::Cad2d_GeoSketch_LineSegment()")
			<< "Invalid Data: " << endl
			<< " - Length: " << theLength << endl
			<< abort(FatalError);
	}

	Handle(Geom2d_Curve) geom = new Geom2d_Line(theP0, theDir);

	Geom2dAPI_ProjectPointOnCurve proj;
	proj.Init(theP0, geom);
	auto pr0 = proj.LowerDistanceParameter();

	proj.Init(theP0 + theLength * Pnt2d(theDir.X(), theDir.Y()), geom);
	auto pr1 = proj.LowerDistanceParameter();

	ChangeGeometry() = new Geom2d_TrimmedCurve(geom, pr0, pr1);
}