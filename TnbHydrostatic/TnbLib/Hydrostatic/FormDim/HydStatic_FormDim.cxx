#include <HydStatic_FormDim.hxx>

#include <Marine_Bodies.hxx>
#include <Marine_CmptLib.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::HydStatic_FormDim::CalcTM()
{
	auto param = Marine_CmptLib::CalcTM(*Body());
	ChangeTM() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcFUW()
{
	auto param = Marine_CmptLib::CalcFUW(*Body());
	ChangeFUW() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcAUW()
{
	auto param = Marine_CmptLib::CalcAUW(*Body());
	ChangeAUW() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcAWL()
{
	auto param = Marine_CmptLib::CalcAWL(*Body());
	ChangeAWL() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcFWL()
{
	auto param = Marine_CmptLib::CalcFWL(*Body());
	ChangeFWL() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcBWL()
{
	auto param = Marine_CmptLib::CalcBWL(*Body());
	ChangeBWL() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcFPP()
{
	auto param = Marine_CmptLib::CalcFPP(*Body());
	ChangeFPP() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcAPP()
{
	auto param = Marine_CmptLib::CalcAPP(*Body());
	ChangeAPP() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcLPP()
{
	auto param = Marine_CmptLib::CalcLPP(APP(), FPP());
	ChangeLPP() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcMPP()
{
	auto param = Marine_CmptLib::CalcMPP(APP(), FPP());
	ChangeMPP() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcLWL()
{
	auto param = Marine_CmptLib::CalcLWL(*Body());
	ChangeLWL() = std::move(param);
}

void tnbLib::HydStatic_FormDim::CalcLOS()
{
	auto param = Marine_CmptLib::CalcLOS(AUW(), FUW());
	ChangeLOS() = std::move(param);
}

tnbLib::HydStatic_FormDim::HydStatic_FormDim()
{
}

tnbLib::HydStatic_FormDim::HydStatic_FormDim
(
	const std::shared_ptr<marineLib::Body_Wetted>& theBody
)
	: theBody_(theBody)
{
}

void tnbLib::HydStatic_FormDim::Perform()
{
	if (NOT Body())
	{
		FatalErrorIn("void tnbLib::HydStatic_FormDim::Perform()")
			<< "the body is not loaded!" << endl
			<< abort(FatalError);
	}

	CalcFUW();
	CalcAUW();
	CalcAWL();
	CalcFWL();

	CalcFPP();
	CalcAPP();
	CalcLPP();
	CalcMPP();
	CalcLWL();
	CalcLOS();

	CalcBWL();

	Change_IsDone() = Standard_True;
}