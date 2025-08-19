#include <Model_DisplNo1.hxx>

#include <Model_CurveParamProfile.hxx>
#include <Model_CorneredSectionVessel.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

#include <algorithm>

std::shared_ptr<tnbLib::Model_ParamProfile> 
tnbLib::Model_DisplNo1::CreateFlareProfile
(
	const std::shared_ptr<Model_SectionVessel>& theSection,
	const Standard_Real theFlare
)
{
	auto section = std::dynamic_pointer_cast<Model_CorneredSectionVessel>(theSection);
	if (NOT section)
	{
		FatalErrorIn(FunctionSIG)
			<< "the section has no corner." << endl
			<< abort(FatalError);
	}

	const auto nbPoints = (Standard_Integer)section->Points().size();
	const auto cornerId = section->CornerId();

	const auto& ctrlPoints = section->Points();

	const auto nbPoles = (Standard_Integer)3;
	TColgp_Array1OfPnt2d Poles(1, nbPoles);

	Poles.SetValue(1, gp_Pnt2d(ctrlPoints.at(cornerId).Y(), ctrlPoints.at(cornerId).Z()));
	Poles.SetValue(3, gp_Pnt2d(ctrlPoints.at(nbPoints - 1).Y(), ctrlPoints.at(nbPoints - 1).Z()));

	Poles.SetValue(2, gp_Pnt2d(Poles.Value(1).X(), Poles.Value(3).Y()));

	TColStd_Array1OfReal Weights(1, nbPoles);
	Weights.Init(1);
	Weights.SetValue(2, std::max(theFlare, MIN_FLARE));

	const auto maxId = nbPoles - 1;
	const auto degree = 2;

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	auto geom = 
		std::make_shared<Model_CurveParamProfile>
		(
			new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, degree)
			);
	return std::move(geom);
}