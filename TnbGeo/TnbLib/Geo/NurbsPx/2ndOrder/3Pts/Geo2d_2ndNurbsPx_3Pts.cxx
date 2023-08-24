#include <Geo2d_2ndNurbsPx_3Pts.hxx>

#include <Geo_ProfileFun_Geom.hxx>
#include <Entity2d_Ray.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>

#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <StdFail_NotDone.hxx>

void tnbLib::Geo2d_2ndNurbsPx_3Pts::Perform()
{
	Pnt2d P0(0, 0);
	Pnt2d P2(Length(), MaxValue());
	Pnt2d Pm0(0, MaxValue());
	auto P1 = Pm0 + Angle() * (P2 - Pm0);

	static const auto nbPoles = (Standard_Integer)nbNodes;
	TColgp_Array1OfPnt2d pnts(1, nbPoles);
	pnts.SetValue(1, P0);
	pnts.SetValue(2, P1);
	pnts.SetValue(3, P2);

	TColStd_Array1OfReal weights(1, nbPoles);
	weights.SetValue(1, 1);
	weights.SetValue(2, Weight());
	weights.SetValue(3, 1);

	TColStd_Array1OfReal knots(1, 2);
	knots.SetValue(1, 0);
	knots.SetValue(2, 1);

	TColStd_Array1OfInteger mults(1, 2);
	mults.SetValue(1, 3);
	mults.SetValue(2, 3);
	try
	{
		auto profile =
			std::make_shared<geoLib::ProfileFun_Geom>
			(
				new Geom2d_BSplineCurve(pnts, weights, knots, mults, 2), 0, Length()
			);
		this->SetProfile(std::move(profile));
	}
	catch (const StdFail_NotDone& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}
	Change_IsDone() = Standard_True;
}