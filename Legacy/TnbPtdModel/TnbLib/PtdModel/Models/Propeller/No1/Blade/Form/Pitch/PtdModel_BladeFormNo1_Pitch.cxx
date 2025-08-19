#include <PtdModel_BladeFormNo1_Pitch.hxx>

#include <PtdModel_FourParsForm.hxx>
#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeGlobalPars.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	word ptdModel::BladeFormNo1_Pitch::ROOT_PITCH = "RootPitch";
	word ptdModel::BladeFormNo1_Pitch::ROOT_STEEP = "RootSteep";
	word ptdModel::BladeFormNo1_Pitch::TIP_PITCH = "TipPitch";
	word ptdModel::BladeFormNo1_Pitch::TIP_STEEP = "TipSteep";

	word ptdModel::BladeFormNo1_Pitch::TypeName_ = "Pitch";
}

#define GetId(par) (size_t)Parameters::par

void tnbLib::ptdModel::BladeFormNo1_Pitch::Init()
{
	theParameters_[GetId(rootPitch)] = ROOT_PITCH;
	theParameters_[GetId(rootSteep)] = ROOT_STEEP;
	theParameters_[GetId(tipPitch)] = TIP_PITCH;
	theParameters_[GetId(tipSteep)] = TIP_STEEP;
}

Standard_Integer tnbLib::ptdModel::BladeFormNo1_Pitch::NbParameters() const
{
	return 4;
}

tnbLib::word
tnbLib::ptdModel::BladeFormNo1_Pitch::GetTypeName() const
{
	return TypeName_;
}

tnbLib::word 
tnbLib::ptdModel::BladeFormNo1_Pitch::Parameter
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
tnbLib::ptdModel::BladeFormNo1_Pitch::CreateForm() const
{
	auto form = std::make_shared<PtdModel_FourParsForm>();
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
tnbLib::ptdModel::BladeFormNo1_Pitch::CreateProfile
(
	const std::shared_ptr<PtdModel_GlobalPars>& theGlobal,
	const std::shared_ptr<PtdModel_Form>& theForm
) const
{
	if (NOT theGlobal)
	{
		FatalErrorIn(FunctionSIG)
			<< "no global parameter has been found!" << endl
			<< abort(FatalError);
	}

	auto global = std::dynamic_pointer_cast<PtdModel_BladeGlobalPars>(theGlobal);
	Debug_Null_Pointer(global);

	const auto rH = global->HubRadius()->Value();
	const auto dia = global->Diameter()->Value();

	auto parMap = theForm->Parameters();

	Pnt2d p0(rH, GetParameter(Parameters::rootPitch));
	Pnt2d p2(dia / 2.0, GetParameter(Parameters::tipPitch));

	const auto dx = std::abs(p2.X() - p0.X());
	const auto dy = std::abs(p2.Y() - p0.Y());
	const auto theta0 = GetParameter(Parameters::rootSteep)*std::atan(dx / dy);
	const auto theta2 = GetParameter(Parameters::tipSteep)*std::atan(dy / dx);

	Dir2d t0(std::sin(theta0), -std::cos(theta0));
	Dir2d t2(-std::cos(theta2), std::sin(theta2));

	Pnt2d p1;
	if (std::abs(t0.Crossed(t2)) <= EPS6)
	{
		p1 = MEAN(p0, p2);
	}
	else
	{
		Standard_Real gamma0, gamma1;
		auto ent = Geo_Tools::IntersectTwoLines(p0, t0, p2, t2, gamma0, gamma1, 1.0E-7);
		p1 = ent.first;
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