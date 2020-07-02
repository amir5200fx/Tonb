#include <HydStatic_FormCoeff.hxx>

#include <HydStatic_FormDim.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_CmptLib.hxx>
#include <Marine_System.hxx>
#include <Marine_Bodies.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::HydStatic_FormCoeff::CalcDISPV
(
	const marineLib::Body_Wetted& theBody
)
{
	auto param = Marine_CmptLib::CalcDISPV(theBody, sysLib::gl_marine_integration_info);
	ChangeDISPV() = std::move(param);
}

void tnbLib::HydStatic_FormCoeff::CalcCB
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& dim = *FormDim();

	ChangeCB()() = DISPV()() / (dim.BWL()()*dim.LWL()()*dim.TM()());
}

void tnbLib::HydStatic_FormCoeff::CalcAM
(
	const marineLib::Body_Wetted& theBody
)
{
	Debug_Null_Pointer(theBody.Mid());
	const auto& mid = *theBody.Mid();

	auto param = Marine_CmptLib::CalcAM(theBody, sysLib::gl_marine_integration_info);
	ChangeAM() = std::move(param);
}

void tnbLib::HydStatic_FormCoeff::CalcCP()
{
	const auto& dim = *FormDim();
	ChangeCP()() = AM()() / (dim.BWL()()*dim.TM()());
}

void tnbLib::HydStatic_FormCoeff::CalcCM()
{
	const auto& dim = *FormDim();
	ChangeCM()() = AM()() / (dim.BWL()()*dim.TM()());
}

//void tnbLib::HydStatic_FormCoeff::CalcAW
//(
//	const marineLib::Body_Wetted& theBody
//)
//{
//	Debug_Null_Pointer(theBody.WL());
//
//	auto param = Marine_CmptLib::CalcAW(*theBody.WL(), sysLib::gl_marine_integration_info);
//	ChangeAW() = std::move(param);
//}

void tnbLib::HydStatic_FormCoeff::CalcCWL()
{
	const auto& dim = *FormDim();

	auto param = Marine_CmptLib::CalcCWL(AW(), dim.LWL(), dim.BWL());
	ChangeCWL() = std::move(param);
}

void tnbLib::HydStatic_FormCoeff::CalcCVP()
{
	const auto& dim = *FormDim();

	auto param = Marine_CmptLib::CalcCVP(DISPV(), AW(), dim.TM());
	ChangeCVP() = std::move(param);
}

tnbLib::HydStatic_FormCoeff::HydStatic_FormCoeff()
{
}

tnbLib::HydStatic_FormCoeff::HydStatic_FormCoeff
(
	const std::shared_ptr<HydStatic_FormDim>& theFormDim
)
	: theFormDim_(theFormDim)
{
}

void tnbLib::HydStatic_FormCoeff::Perform()
{
	if (NOT FormDim())
	{
		FatalErrorIn("void tnbLib::HydStatic_FormCoeff::Perform()")
			<< "no formDim is loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT FormDim()->IsDone())
	{
		FatalErrorIn("void tnbLib::HydStatic_FormCoeff::Perform()")
			<< "formDim is not performed!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(FormDim()->Body());
	const auto& body = *FormDim()->Body();

	CalcDISPV(body);
	CalcCB(body);
	CalcAM(body);

	CalcCP();
	CalcCM();

	CalcAW(body);

	CalcCWL();
	CalcCVP();

	Change_IsDone() = Standard_True;
}