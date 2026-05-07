#include <SectPx_Curve.hxx>

#include <SectPx_TopoProfile.hxx>
#include <SectPx_KnotVector.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/StdFail_NotDone.hxx>
#include <opencascade/BSplCLib.hxx>
#include <opencascade/Geom2d_BSplineCurve.hxx>
#include <opencascade/TColStd_Array1OfReal.hxx>
#include <opencascade/TColStd_Array1OfInteger.hxx>
#include <opencascade/TColgp_Array1OfPnt2d.hxx>

void tnbLib::SectPx_Curve::Perform(const Standard_Integer deg)
{
	if (NOT KnotAlg())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no algorithm for creating a knot vector" << endl
			<< abort(FatalError);
	}

	if (NOT Profile())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is no profile to make a curve" << endl
			<< abort(FatalError);
	}

	auto pnts = Profile()->RetrieveCoords();
	auto knotVector = KnotAlg()->CreateKnots(pnts, deg);

	TColStd_Array1OfReal knotsSeq(1, (Standard_Integer)knotVector.size());
	for (Standard_Integer i = 1; i <= knotVector.size(); i++)
	{
		knotsSeq.SetValue(i, knotVector[i - 1]);
	}

	TColStd_Array1OfReal knots;
	TColStd_Array1OfInteger mults;
	BSplCLib::Knots(knotsSeq, knots, mults);

	TColgp_Array1OfPnt2d Poles(1, (Standard_Integer)pnts.size());
	for (Standard_Integer i = 1; i <= pnts.size(); i++)
	{
		Poles.SetValue(i, pnts[i - 1]);
	}

	try
	{
		Handle(Geom2d_BSplineCurve) curve =
			new Geom2d_BSplineCurve(Poles, knots, mults, deg);
		ChangeGeometry() = std::move(curve);
	}
	catch (const StdFail_NotDone& x)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to create bspline curve: " << endl
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}

	Change_IsDone() = Standard_True;
}