#include <GeoSketch2d_HypbcArc.hxx>

#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <GCE2d_MakeArcOfHyperbola.hxx>

tnbLib::GeoSketch2d_HypbcArc::GeoSketch2d_HypbcArc
(
	const gp_Hypr2d & theHypr, 
	const Standard_Real theAlpha0,
	const Standard_Real theAlpha1, 
	const Standard_Boolean theSense
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfHyperbola(theHypr, theAlpha0, theAlpha1, theSense);

		ChangeGeometry() = t;
	}
	catch (const std::exception&)
	{
		FatalErrorIn("GeoSketch2d_HypbcArc::GeoSketch2d_HypbcArc()")
			<< "the makeOfHyperbola algorithm is not done!" << endl
			<< abort(FatalError);
	}
}

tnbLib::GeoSketch2d_HypbcArc::GeoSketch2d_HypbcArc
(
	const gp_Hypr2d & theHypr, 
	const Pnt2d & theP,
	const Standard_Real theAlpha,
	const Standard_Boolean theSense
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfHyperbola(theHypr, theP, theAlpha, theSense);

		ChangeGeometry() = t;
	}
	catch (const std::exception&)
	{
		FatalErrorIn("GeoSketch2d_HypbcArc::GeoSketch2d_HypbcArc()")
			<< "the makeOfHyperbola algorithm is not done!" << endl
			<< abort(FatalError);
	}
}

tnbLib::GeoSketch2d_HypbcArc::GeoSketch2d_HypbcArc
(
	const gp_Hypr2d & theHypr,
	const Pnt2d & theP0, 
	const Pnt2d & theP1,
	const Standard_Boolean theSense
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfHyperbola(theHypr, theP0, theP1, theSense);

		ChangeGeometry() = t;
	}
	catch (const std::exception&)
	{
		FatalErrorIn("GeoSketch2d_HypbcArc::GeoSketch2d_HypbcArc()")
			<< "the makeOfHyperbola algorithm is not done!" << endl
			<< abort(FatalError);
	}
}