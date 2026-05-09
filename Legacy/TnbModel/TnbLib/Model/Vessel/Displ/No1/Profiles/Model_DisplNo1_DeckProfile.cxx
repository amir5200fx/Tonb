#include <Model_DisplNo1.hxx>

#include <Model_CurveParamProfile.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

std::shared_ptr<tnbLib::Model_ParamProfile> 
tnbLib::Model_DisplNo1::CreateDeckProfile() const
{
	//  P2 ----- P3 ----- P4 ----- P5 ----- P6
	//  |									|
	//	|									|
	//	|									|
	//	P1									P7
	const auto& dimens = Parameters().Dimensions();
	const auto& hull = Parameters().Hull();
	const auto& transom = Parameters().Transom();
	const auto& stem = Parameters().Stem();

	const auto beam = dimens.BeamOnDeck()->Value();
	const auto length = dimens.LengthOnDeck()->Value();

	auto P1 = Pnt2d(0, transom.Width()->Value() * beam);
	auto P2 = Pnt2d(0, beam);
	auto P4 = Pnt2d(hull.MaxAreaLocation()->Value() * length, beam);
	auto P6 = Pnt2d(length, beam);
	auto P7 = Pnt2d(length, stem.BowRounding()->Value() * beam);

	auto P3 = P4 + (P2 - P4) * hull.AftFullness()->Value();
	auto P5 = P4 + 0.95 * (P6 - P4) * hull.FwdFullness()->Value();

	static const Standard_Integer nbPoles = 7;
	TColgp_Array1OfPnt2d Poles(1, nbPoles);

	Poles.SetValue(1, P1);
	Poles.SetValue(2, P2);
	Poles.SetValue(3, P3);
	Poles.SetValue(4, P4);
	Poles.SetValue(5, P5);
	Poles.SetValue(6, P6);
	Poles.SetValue(7, P7);

	TColStd_Array1OfReal Weights(1, nbPoles);
	Weights.Init(1);

	const auto MaxIndex = nbPoles - 1;
	const Standard_Integer Degree = 2;

	TColStd_Array1OfReal Knots(1, 4);
	TColStd_Array1OfInteger Mults(1, 4);

	Knots.SetValue(1, 0);
	Knots.SetValue(2, 0.25);
	Knots.SetValue(3, 0.75);
	Knots.SetValue(4, 1);

	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 2);
	Mults.SetValue(4, 3);

	auto geom = 
		std::make_shared<Model_CurveParamProfile>
		(new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree));
	return std::move(geom);
}