#include <Cad_CurveTools.hxx>

#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/GC_MakeSegment.hxx>
#include <opencascade/GeomAPI_Interpolate.hxx>
#include <opencascade/TColgp_HArray1OfPnt.hxx>
#include <opencascade/StdFail_NotDone.hxx>

Handle(Geom_Curve)
tnbLib::Cad_CurveTools::Interpolation
(
	const std::vector<Pnt3d>& theQ,
	const Standard_Boolean thePeriodic,
	const Standard_Real theTol
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn("void Perform()")
			<< "Not enough offset points to interpolate" << endl
			<< abort(FatalError);
	}

	Handle(TColgp_HArray1OfPnt) Q =
		new TColgp_HArray1OfPnt(1, (Standard_Integer)theQ.size());
	Standard_Integer K = 0;
	for (const auto& x : theQ)
	{
		Q->SetValue(K + 1, x);

		++K;
	}

	try
	{
		GeomAPI_Interpolate interp(Q, thePeriodic, theTol);
		interp.Perform();

		return interp.Curve();
	}
	catch (const StdFail_NotDone& f)
	{
		FatalErrorIn(FunctionSIG)
			<< "catch an exception in 'GeomAPI_Interpolate' algorithm" << endl
			<< " message: " << f.GetMessageString() << endl;
		return nullptr;
	}
}

opencascade::handle<Geom_Curve>
tnbLib::Cad_CurveTools::MakeSegment(const Pnt3d& theP0, const Pnt3d& theP1)
{
	GC_MakeSegment maker(theP0, theP1);
	if (maker.IsDone())
	{
		const auto& geom = maker.Value();
		return std::move(geom);
	}
	else
	{
		return nullptr;
	}
}
