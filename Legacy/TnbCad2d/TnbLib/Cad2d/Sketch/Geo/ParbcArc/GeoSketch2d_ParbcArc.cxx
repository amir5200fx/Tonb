#include <GeoSketch2d_ParbcArc.hxx>

#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/GCE2d_MakeArcOfParabola.hxx>

tnbLib::GeoSketch2d_ParbcArc::GeoSketch2d_ParbcArc
(
	const gp_Parab2d & theParab,
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1, 
	const Standard_Boolean theSense)

{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfParabola(theParab, theAlpha0, theAlpha1, theSense);

		ChangeGeometry() = t;
	}
	catch (const std::exception&)
	{
		FatalErrorIn("GeoSketch2d_ParbcArc::GeoSketch2d_ParbcArc()")
			<< "the makeOfParabola algorithm is not done!" << endl
			<< abort(FatalError);
	}
}

tnbLib::GeoSketch2d_ParbcArc::GeoSketch2d_ParbcArc
(
	const gp_Parab2d & theParab, 
	const Pnt2d & theP,
	const Standard_Real theAlpha,
	const Standard_Boolean theSense
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfParabola(theParab, theP, theAlpha, theSense);

		ChangeGeometry() = t;
	}
	catch (const std::exception&)
	{
		FatalErrorIn("GeoSketch2d_ParbcArc::GeoSketch2d_ParbcArc()")
			<< "the makeOfParabola algorithm is not done!" << endl
			<< abort(FatalError);
	}
}

tnbLib::GeoSketch2d_ParbcArc::GeoSketch2d_ParbcArc
(
	const gp_Parab2d & theParab,
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const Standard_Boolean theSense
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfParabola(theParab, theP0, theP1, theSense);

		ChangeGeometry() = t;
	}
	catch (const std::exception&)
	{
		FatalErrorIn("GeoSketch2d_ParbcArc::GeoSketch2d_ParbcArc()")
			<< "the makeOfParabola algorithm is not done!" << endl
			<< abort(FatalError);
	}
}