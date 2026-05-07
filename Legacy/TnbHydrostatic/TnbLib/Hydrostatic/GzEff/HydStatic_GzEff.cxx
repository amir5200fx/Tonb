#include <HydStatic_GzEff.hxx>

#include <Marine_xSectionParam.hxx>
#include <Marine_System.hxx>
#include <HydStatic_rArmCurves.hxx>
#include <HydStatic_rArmCurve_Eff.hxx>
#include <HydStatic_SolutionData_GzEff.hxx>
#include <HydStatic_CmptLib.hxx>
#include <HydStatic_Tools.hxx>
#include <HydStatic_CurveMaker.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::HydStatic_GzEff::Perform()
{
	if (NOT BodyGz())
	{
		FatalErrorIn(FunctionSIG)
			<< "no GZ body hull has been loaded!" << endl
			<< abort(FatalError);
	}

	if (theTanks_)
	{
		auto rArm = 
			HydStatic_CmptLib::CalcEffectiveRightingArm(theBody_, theTanks_);
		theEff_ = std::move(rArm);
	}

	if (NOT theEff_)
	{
		theEff_ = HydStatic_CmptLib::CalcEffectiveRightingArm(theBody_);
	}
	Debug_Null_Pointer(theEff_);

	HydStatic_Tools::AuCurve(theEff_, hydStcLib::RetrieveType(theBody_), 0, sysLib::gl_marine_integration_info);
	
	Change_IsDone() = Standard_True;
}