#include <PtdModel_BladeFormNo1_Rake.hxx>

#include <PtdModel_UniformForm.hxx>
#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeGlobalPars.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	word ptdModel::BladeFormNo1_Rake::TIP_RAKE = "TipRake";
}

void tnbLib::ptdModel::BladeFormNo1_Rake::Init()
{
	theParameter_ = TIP_RAKE;
}

Standard_Integer 
tnbLib::ptdModel::BladeFormNo1_Rake::NbParameters() const
{
	return 1;
}

tnbLib::word 
tnbLib::ptdModel::BladeFormNo1_Rake::Parameter(const Standard_Integer /*theIndex*/) const
{
	return theParameter_;
}

std::shared_ptr<tnbLib::PtdModel_Form> 
tnbLib::ptdModel::BladeFormNo1_Rake::CreateForm() const
{
	auto form = std::make_shared<PtdModel_UniformForm>();
	Debug_Null_Pointer(form);

	auto x = PtdModel_FormMaker::Parameter(Parameter(0));
	form->SetValue(std::move(x));
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
tnbLib::ptdModel::BladeFormNo1_Rake::CreateProfile
(
	const std::shared_ptr<PtdModel_BladeGlobalPars>& theGlobal,
	const std::shared_ptr<PtdModel_Form>& theForm
) const
{
	auto parMap = theForm->Parameters();

	Pnt2d p0(0, 0);
	Pnt2d p1(theGlobal->Diameter()->Value() / 2, GetParameter(Parameters::tipRake));

	Standard_Integer NbPoles = 2;
	Standard_Integer Degree = 1;

	TColgp_Array1OfPnt2d Poles(1, NbPoles);
	Poles.SetValue(1, p0);
	Poles.SetValue(2, p1);

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 2);
	Mults.SetValue(2, 2);

	auto profile = PtdModel_BladeProfile::MakeProfile(Poles, Weights, Knots, Mults, Degree);
	return std::move(profile);
}