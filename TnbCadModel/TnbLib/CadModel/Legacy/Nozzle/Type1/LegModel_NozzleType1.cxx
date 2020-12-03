#include <LegModel_NozzleType1.hxx>

#include <Pnt2d.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <StdFail_NotDone.hxx>

#include <vector>

#define Linear_Intrpl(x0, x1, t) (x0 + t*(x1-x0))

void tnbLib::LegModel_NozzleType1::CreateProfile()
{
	static const Standard_Integer nbPoles = 17;

	TColgp_Array1OfPnt2d pnts(1, nbPoles);

	Pnt2d P0(0, Parameters().RadiusAtInlet()->Value());
	Pnt2d P16(Parameters().OverallLength()->Value(), Parameters().RadiusAtOutlet()->Value());
	Pnt2d P8(Linear_Intrpl(P0.X(), P16.X(), Parameters().Throat()->Value()), Linear_Intrpl(0, P0.Y(), Parameters().RadiusAtThroat()->Value()));

	const auto& inlet = *Parameters().InletProfile();
	const auto& outlet = *Parameters().OutletProfile();
	Pnt2d P2(Linear_Intrpl(P0.X(), P8.X(), inlet.OffsetAtInlet()->Value()), P0.Y());
	Pnt2d P6(Linear_Intrpl(P8.X(), P2.X(), inlet.OffsetAtThroat()->Value()), P8.Y());
	auto P4 = Linear_Intrpl(P6, P2, inlet.Inflection()->Value());

	auto P1 = Linear_Intrpl(P2, P0, inlet.Rounding1()->Value());
	auto P3 = Linear_Intrpl(P2, P4, inlet.Rounding1()->Value());

	auto P5 = Linear_Intrpl(P6, P4, inlet.Rounding2()->Value());
	auto P7 = Linear_Intrpl(P6, P8, inlet.Rounding2()->Value());

	const auto theta = atan((P16.Y() - P8.Y()) / (P16.X() - P8.X()));
	const auto y = (P16.X() - P8.X())*tan(Linear_Intrpl(0, theta, outlet.TangentAtOutlet()->Value()));
	auto P14 = Linear_Intrpl(P16, Pnt2d(P8.X(), P16.Y() - y), outlet.OffsetAtOutlet()->Value());
	Pnt2d P10(Linear_Intrpl(P8.X(), P14.X(), outlet.OffsetAtThroat()->Value()), P8.Y());
	auto P12 = Linear_Intrpl(P10, P14, outlet.Inflection()->Value());

	auto P9 = Linear_Intrpl(P10, P8, outlet.Rounding1()->Value());
	auto P11 = Linear_Intrpl(P10, P12, outlet.Rounding1()->Value());

	auto P13 = Linear_Intrpl(P14, P12, outlet.Rounding2()->Value());
	auto P15 = Linear_Intrpl(P14, P16, outlet.Rounding2()->Value());

	pnts.SetValue(1, P0);
	pnts.SetValue(2, P1);
	pnts.SetValue(3, P2);
	pnts.SetValue(4, P3);
	pnts.SetValue(5, P4);
	pnts.SetValue(6, P5);
	pnts.SetValue(7, P6);
	pnts.SetValue(8, P7);
	pnts.SetValue(9, P8);
	pnts.SetValue(10, P9);
	pnts.SetValue(11, P10);
	pnts.SetValue(12, P11);
	pnts.SetValue(13, P12);
	pnts.SetValue(14, P13);
	pnts.SetValue(15, P14);
	pnts.SetValue(16, P15);
	pnts.SetValue(17, P16);

	TColStd_Array1OfReal weights(1, nbPoles);
	for (Standard_Integer i = 1; i <= weights.Size(); i++)
	{
		weights.SetValue(i, 1.0);
	}
	weights.SetValue(3, inlet.RoundingWeight1()->Value());
	weights.SetValue(7, inlet.RoundingWeight2()->Value());

	weights.SetValue(11, outlet.RoundingWeight1()->Value());
	weights.SetValue(15, outlet.RoundingWeight1()->Value());

	static const auto du = (Standard_Real)0.125;
	TColStd_Array1OfReal knots(1, 9);
	knots.SetValue(1, 0);

	knots.SetValue(2, du);

	knots.SetValue(3, 0.25);

	knots.SetValue(4, 0.25 + du);

	knots.SetValue(5, 0.5);

	knots.SetValue(6, 0.5 + du);

	knots.SetValue(7, 0.75);

	knots.SetValue(8, 0.75 + du);

	knots.SetValue(9, 1.0);

	TColStd_Array1OfInteger mults(1, 9);
	mults.SetValue(1, 4);
	mults.SetValue(2, 1);
	mults.SetValue(3, 3);
	mults.SetValue(4, 1);
	mults.SetValue(5, 3);
	mults.SetValue(6, 1);
	mults.SetValue(7, 3);
	mults.SetValue(8, 1);
	mults.SetValue(9, 4);

	try
	{
		theProfile_ = new Geom2d_BSplineCurve(pnts, weights, knots, mults, 3);
	}
	catch (const StdFail_NotDone& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}
}

void tnbLib::LegModel_NozzleType1::Perform()
{
	CreateProfile();

	Change_IsDone() = Standard_True;
	
}