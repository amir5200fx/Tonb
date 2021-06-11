#include <PtdModel_BladeFormNo1_Skew.hxx>

#include <PtdModel_ThreeParsForm.hxx>
#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeGlobalPars.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	word ptdModel::BladeFormNo1_Skew::ROOT_STEEP = "RootSteep";
	word ptdModel::BladeFormNo1_Skew::TIP_SKEW = "TipSkew";
	word ptdModel::BladeFormNo1_Skew::TIP_STEEP = "TipSteep";

	word ptdModel::BladeFormNo1_Skew::TypeName_ = "Skew";
}

#define GetId(par) (size_t)Parameters::par

void tnbLib::ptdModel::BladeFormNo1_Skew::Init()
{
	theParameters_[GetId(rootSteep)] = ROOT_STEEP;
	theParameters_[GetId(tipSkew)] = TIP_SKEW;
	theParameters_[GetId(tipSteep)] = TIP_STEEP;
}

Standard_Integer tnbLib::ptdModel::BladeFormNo1_Skew::NbParameters() const
{
	return 3;
}

tnbLib::word
tnbLib::ptdModel::BladeFormNo1_Skew::GetTypeName() const
{
	return TypeName_;
}

tnbLib::word 
tnbLib::ptdModel::BladeFormNo1_Skew::Parameter(const Standard_Integer theIndex) const
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
tnbLib::ptdModel::BladeFormNo1_Skew::CreateForm() const
{
	auto form = std::make_shared<PtdModel_ThreeParsForm>();
	Debug_Null_Pointer(form);

	form->SetName(GetTypeName());

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
#include <PtdModel_Profile.hxx>

#include <Standard_Handle.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <Geom2d_BSplineCurve.hxx>

#define GetParameter(par) PtdModel_Form::Parameter(Parameter((int)par), parMap)->Value()

std::shared_ptr<tnbLib::PtdModel_Profile> 
tnbLib::ptdModel::BladeFormNo1_Skew::CreateProfile
(
	const std::shared_ptr<PtdModel_GlobalPars>& theGlobal,
	const std::shared_ptr<PtdModel_Form>& theForm
) const
{
	auto global = std::dynamic_pointer_cast<PtdModel_BladeGlobalPars>(theGlobal);
	Debug_Null_Pointer(global);

	const auto rH = global->HubRadius()->Value();
	const auto dia = global->Diameter()->Value();

	auto parMap = theForm->Parameters();

	Pnt2d p0(rH, 0);
	Pnt2d p2(dia / 2.0, GetParameter(Parameters::tipSkew));

	const auto dx = std::abs(p2.X() - p0.X());
	const auto dy = std::abs(p2.Y() - p0.Y());

	const auto maxTheta0 = std::atan(dy / dx);
	const auto minTheta0 = -0.5*maxTheta0;

	const auto theta0 = minTheta0 + GetParameter(Parameters::rootSteep)*(maxTheta0 - minTheta0);
	const auto theta2 = GetParameter(Parameters::tipSteep)*std::atan(dx / dy);

	Dir2d t0(std::cos(theta0), std::sin(theta0));
	Dir2d t2(-std::sin(theta2), -std::cos(theta2));

	Pnt2d p1;
	if (std::abs(t0.Crossed(t2)) < EPS6)
	{
		p1 = MEAN(p0, p2);
	}
	else
	{
		p1 = Geo_Tools::IntersectionTwoLines(p0, t0, p2, t2, 1.0E-7);
	}

	Standard_Integer NbPoles = 3;
	Standard_Integer Degree = 2;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, p0);
	Poles.SetValue(2, p1);
	Poles.SetValue(3, p2);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	auto profile = PtdModel_Profile::MakeProfile(Poles, Weights, Knots, Mults, Degree);
	Debug_Null_Pointer(profile);

	profile->SetName(GetTypeName());
	return std::move(profile);
}