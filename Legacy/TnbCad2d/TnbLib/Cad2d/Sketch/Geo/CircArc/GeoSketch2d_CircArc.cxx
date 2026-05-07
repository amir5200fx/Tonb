#include <GeoSketch2d_CircArc.hxx>

#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/gp_Circ2d.hxx>
#include <opencascade/Geom2d_TrimmedCurve.hxx>
#include <opencascade/GCE2d_MakeArcOfCircle.hxx>
#include <opencascade/StdFail_NotDone.hxx>

tnbLib::GeoSketch2d_CircArc::GeoSketch2d_CircArc
(
	const gp_Circ2d & theCirc, 
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1, 
	const Standard_Boolean theSense
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfCircle(theCirc, theAlpha0, theAlpha1, theSense);

		ChangeGeometry() = t;
	}
	catch (const StdFail_NotDone&)
	{
		FatalErrorIn("GeoSketch2d_CircArc::GeoSketch2d_CircArc()")
			<< "the makeOfCircle algorithm is not done!" << endl
			<< abort(FatalError);
	}
}

tnbLib::GeoSketch2d_CircArc::GeoSketch2d_CircArc
(
	const gp_Circ2d & theCirc,
	const Pnt2d & theP,
	const Standard_Real theAlpha,
	const Standard_Boolean theSense
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfCircle(theCirc, theP, theAlpha, theSense);

		ChangeGeometry() = t;
	}
	catch (const StdFail_NotDone&)
	{
		FatalErrorIn("GeoSketch2d_CircArc::GeoSketch2d_CircArc()")
			<< "the makeOfCircle algorithm is not done!" << endl
			<< abort(FatalError);
	}
}

tnbLib::GeoSketch2d_CircArc::GeoSketch2d_CircArc
(
	const gp_Circ2d & theCirc,
	const Pnt2d & theP0,
	const Pnt2d & theP1, 
	const Standard_Boolean theSense
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfCircle(theCirc, theP0, theP1, theSense);

		ChangeGeometry() = t;
	}
	catch (const StdFail_NotDone&)
	{
		FatalErrorIn("GeoSketch2d_CircArc::GeoSketch2d_CircArc()")
			<< "the makeOfCircle algorithm is not done!" << endl
			<< abort(FatalError);
	}
}

tnbLib::GeoSketch2d_CircArc::GeoSketch2d_CircArc
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Pnt2d & theP2
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfCircle(theP0, theP1, theP2);

		ChangeGeometry() = t;
	}
	catch (const StdFail_NotDone&)
	{
		FatalErrorIn("GeoSketch2d_CircArc::GeoSketch2d_CircArc()")
			<< "the makeOfCircle algorithm is not done!" << endl
			<< abort(FatalError);
	}
}