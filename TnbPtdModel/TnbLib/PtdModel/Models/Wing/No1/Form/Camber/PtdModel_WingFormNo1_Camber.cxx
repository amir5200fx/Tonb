#include <PtdModel_WingFormNo1_Camber.hxx>

#include <PtdModel_UniformForm.hxx>
#include <PtdModel_Pars.hxx>
#include <PtdModel_WingGlobalPars.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	word ptdModel::WingFormNo1_Camber::ROOT_CAMBER = "RootCamber";
	word ptdModel::WingFormNo1_Camber::TypeName_ = "Camber";
}

void tnbLib::ptdModel::WingFormNo1_Camber::Init()
{
	theParameter_ = ROOT_CAMBER;
}

Standard_Integer 
tnbLib::ptdModel::WingFormNo1_Camber::NbParameters() const
{
	return 1;
}

tnbLib::word 
tnbLib::ptdModel::WingFormNo1_Camber::GetTypeName() const
{
	return TypeName_;
}

tnbLib::word 
tnbLib::ptdModel::WingFormNo1_Camber::Parameter
(
	const Standard_Integer /*theIndex*/
) const
{
	return theParameter_;
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

std::shared_ptr<tnbLib::PtdModel_Form> 
tnbLib::ptdModel::WingFormNo1_Camber::CreateForm() const
{
	auto form = std::make_shared<PtdModel_UniformForm>();
	Debug_Null_Pointer(form);

	form->SetName(GetTypeName());

	auto x = PtdModel_FormMaker::Parameter(Parameter(0));
	form->SetValue(std::move(x));
	return std::move(form);
}

std::shared_ptr<tnbLib::PtdModel_Profile> 
tnbLib::ptdModel::WingFormNo1_Camber::CreateProfile
(
	const std::shared_ptr<PtdModel_GlobalPars>& theGlobal,
	const std::shared_ptr<PtdModel_Form>& theForm
) const
{
	auto global = std::dynamic_pointer_cast<PtdModel_WingGlobalPars>(theGlobal);
	Debug_Null_Pointer(global);

	const auto s = global->SpanLength()->Value();

	auto parMap = theForm->Parameters();

	Pnt2d p0(0, GetParameter(Parameters::rootCamber));
	Pnt2d p1(s, GetParameter(Parameters::rootCamber));

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

	auto profile = PtdModel_Profile::MakeProfile(Poles, Weights, Knots, Mults, Degree);
	Debug_Null_Pointer(profile);

	profile->SetName(GetTypeName());
	return std::move(profile);
}