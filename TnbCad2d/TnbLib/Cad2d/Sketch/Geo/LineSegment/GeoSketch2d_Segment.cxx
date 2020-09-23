#include <GeoSketch2d_Segment.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Vec2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Precision.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

tnbLib::GeoSketch2d_Segment::GeoSketch2d_Segment
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	if (theP1.Distance(theP0) <= Precision::Confusion())
	{
		FatalErrorIn("CGeoSketch2d_Segment::GeoSketch2d_Segment()")
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

tnbLib::GeoSketch2d_Segment::GeoSketch2d_Segment
(
	const Pnt2d & theP0, 
	const Dir2d & theDir, 
	const Standard_Real theLength
)
{
	if (theLength <= Precision::Confusion())
	{
		FatalErrorIn("GeoSketch2d_Segment::GeoSketch2d_Segment()")
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

tnbLib::GeoSketch2d_Segment::GeoSketch2d_Segment
(
	const Pnt2d & theP0,
	const Standard_Real theAngle,
	const Standard_Real theLength
)
{
	if (theLength <= Precision::Confusion())
	{
		FatalErrorIn("GeoSketch2d_Segment::GeoSketch2d_Segment()")
			<< "Invalid Data: " << endl
			<< " - Length: " << theLength << endl
			<< abort(FatalError);
	}

	Dir2d dir(cos(theAngle), sin(theAngle));
	Handle(Geom2d_Curve) geom = new Geom2d_Line(theP0, dir);

	Geom2dAPI_ProjectPointOnCurve proj;
	proj.Init(theP0, geom);
	auto pr0 = proj.LowerDistanceParameter();

	proj.Init(theP0 + theLength * Pnt2d(dir.X(), dir.Y()), geom);
	auto pr1 = proj.LowerDistanceParameter();

	ChangeGeometry() = new Geom2d_TrimmedCurve(geom, pr0, pr1);
}