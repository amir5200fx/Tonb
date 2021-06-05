#include <PtdModel_BladeFormNo1_Camber.hxx>

#include <PtdModel_SixParsForm.hxx>
#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeGlobalPars.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	word ptdModel::BladeFormNo1_Camber::ROOT_CAMBER = "RootCamber";
	word ptdModel::BladeFormNo1_Camber::TIP_CAMBER = "TipCamber";
	word ptdModel::BladeFormNo1_Camber::MAX_CAMBER = "MaxCamber";
	word ptdModel::BladeFormNo1_Camber::MAX_CAMBER_LOCATION = "MaxCamberLoc";
	word ptdModel::BladeFormNo1_Camber::ROOT_WEIGHT = "RootWeight";
	word ptdModel::BladeFormNo1_Camber::TIP_WEIGHT = "TipWeight";
}

#define GetId(par) (size_t)Parameters::par

void tnbLib::ptdModel::BladeFormNo1_Camber::Init()
{
	theParameters_[GetId(rootCamber)] = ROOT_CAMBER;
	theParameters_[GetId(tipCamber)] = TIP_CAMBER;
	theParameters_[GetId(maxCamber)] = MAX_CAMBER;
	theParameters_[GetId(maxCamberLoc)] = MAX_CAMBER_LOCATION;
	theParameters_[GetId(rootWeight)] = ROOT_WEIGHT;
	theParameters_[GetId(tipWeight)] = TIP_WEIGHT;
}

Standard_Integer 
tnbLib::ptdModel::BladeFormNo1_Camber::NbParameters() const
{
	return Standard_Integer(6);
}

tnbLib::word 
tnbLib::ptdModel::BladeFormNo1_Camber::Parameter
(
	const Standard_Integer theIndex
) const
{
	if (NOT INSIDE(theIndex, 0, NbParameters() - 1))
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid index has been detected!" << endl
			<< abort(FatalError);
	}
	return theParameters_[theIndex];
}

std::shared_ptr<tnbLib::PtdModel_Form> 
tnbLib::ptdModel::BladeFormNo1_Camber::CreateForm() const
{
	auto form = std::make_shared<PtdModel_SixParsForm>();
	Debug_Null_Pointer(form);

	for (int i = 0; i < NbParameters(); i++)
	{
		auto x = PtdModel_FormMaker::Parameter(Parameter(i));
		form->SetX(i, std::move(x));
	}
	return std::move(form);
}

#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Geo_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <PtdModel_BladeProfile.hxx>

#include <Standard_Handle.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <Geom2d_BSplineCurve.hxx>

#define GetParameter(par) PtdModel_Form::Parameter(Parameter((int)par), parMap)->Value()

std::shared_ptr<tnbLib::PtdModel_BladeProfile>
tnbLib::ptdModel::BladeFormNo1_Camber::CreateProfile
(
	const std::shared_ptr<PtdModel_BladeGlobalPars>& theGlobal,
	const std::shared_ptr<PtdModel_Form>& theForm
) const
{
	const auto rH = theGlobal->HubRadius()->Value();
	const auto dia = theGlobal->Diameter()->Value();

	auto parMap = theForm->Parameters();

	Pnt2d p0(rH, GetParameter(Parameters::rootCamber));
	Pnt2d p1(p0.X(), GetParameter(Parameters::maxCamber));
	Pnt2d p2(GetParameter(Parameters::maxCamberLoc)*(dia / 2 - rH) + rH, p1.Y());
	Pnt2d p3(dia / 2, p2.Y());
	Pnt2d p4(p3.X(), GetParameter(Parameters::tipCamber));

	p1 += GetParameter(Parameters::rootWeight)*(p2 - p1);

	Standard_Integer NbPoles = 5;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, p0);
	Poles.SetValue(2, p1);
	Poles.SetValue(3, p2);
	Poles.SetValue(4, p3);
	Poles.SetValue(5, p4);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);
	Weights.SetValue(2, GetParameter(Parameters::rootWeight));
	Weights.SetValue(4, GetParameter(Parameters::tipWeight));

	TColStd_Array1OfReal Knots(1, 3);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 0.5);
	Knots.SetValue(3, 1);

	TColStd_Array1OfInteger Mults(1, 3);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 3);

	auto profile = PtdModel_BladeProfile::MakeProfile(Poles, Weights, Knots, Mults, Degree);
	return std::move(profile);
}