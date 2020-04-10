#include <GeoSketch2d_EllipcArc.hxx>

#include <error.hxx>
#include <OSstream.hxx>

#include <GCE2d_MakeArcOfEllipse.hxx>
#include <StdFail_NotDone.hxx>

tnbLib::GeoSketch2d_EllipcArc::GeoSketch2d_EllipcArc
(
	const gp_Elips2d & theElips, 
	const Standard_Real theAlpha0, 
	const Standard_Real theAlpha1, 
	const Standard_Real theSense
)
{
	try
	{
		Handle(Geom2d_TrimmedCurve) t = GCE2d_MakeArcOfEllipse(theElips, theAlpha0, theAlpha1, theSense);

		ChangeGeometry() = t;
	}
	catch (const std::exception&)
	{
		FatalErrorIn("GeoSketch2d_EllipcArc::GeoSketch2d_EllipcArc()")
			<< "the makeOfEllipse algorithm is not done!" << endl
			<< abort(FatalError);
	}
}