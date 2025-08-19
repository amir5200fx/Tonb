#include <HydStatic_FunLib.hxx>

#include <Geo_xDistb.hxx>
#include <HydStatic_rArmCurve.hxx>
#include <HydStatic_StbFun_hArm.hxx>
#include <HydStatic_StbFun_rArm.hxx>
#include <HydStatic_hArmFormula.hxx>
#include <HydStatic_StbFun_IntgFun.hxx>
#include <HydStatic_Tools.hxx>
#include <NumAlg_AdaptiveInteg.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::Geo_xDistb> 
tnbLib::HydStatic_FunLib::RetrieveHeelDistb
(
	const hydStcLib::StbFun_rArm& theRighting
)
{
	auto distb = std::make_shared<Geo_xDistb>();
	Debug_Null_Pointer(distb);

	distb->SetLower(theRighting.MinHeel());
	distb->SetUpper(theRighting.MaxHeel());

	const auto& arm = theRighting.Arm();
	const auto& Qs = arm->Qs();

	auto& values = distb->ChangeValues();
	values.reserve(Qs.size());
	for (const auto& x : Qs)
	{
		values.push_back(x.Heel());
	}
	return std::move(distb);
}

std::shared_ptr<tnbLib::HydStatic_StbFun> 
tnbLib::HydStatic_FunLib::HeelingArm
(
	const std::shared_ptr<HydStatic_hArmFormula>& theHeeling, 
	const std::shared_ptr<HydStatic_StbFun>& theRighting,
	const hydStcLib::CurveMakerType t
)
{
	Debug_Null_Pointer(theRighting);

	auto rArm = std::dynamic_pointer_cast<hydStcLib::StbFun_rArm>(theRighting);
	Debug_Null_Pointer(rArm);

	const auto distb = RetrieveHeelDistb(*rArm);
	Debug_Null_Pointer(distb);

	auto hArm = HeelingArm(theHeeling, *distb, t);
	return std::move(hArm);
}

std::shared_ptr<tnbLib::HydStatic_StbFun> 
tnbLib::HydStatic_FunLib::HeelingArm
(
	const std::shared_ptr<HydStatic_hArmFormula>& theHeeling, 
	const Geo_xDistb & theDist,
	const hydStcLib::CurveMakerType t
)
{
	std::vector<HydStatic_GzQP> Qs;
	for (const auto x : theDist.Values())
	{
		auto lever = theHeeling->Value(x);

		HydStatic_GzQP q(x, lever, 0);
		Qs.push_back(std::move(q));
	}

	auto hArm = HydStatic_Tools::HeelingCurve(std::move(Qs), t);
	Debug_Null_Pointer(hArm);

	auto fun = std::make_shared<hydStcLib::StbFun_hArm>(std::move(hArm));
	Debug_Null_Pointer(fun);

	return std::move(fun);
}

Standard_Real 
tnbLib::HydStatic_FunLib::Area
(
	const std::shared_ptr<HydStatic_StbFun>& theFun, 
	const Standard_Real thePhi0,
	const Standard_Real thePhi1, 
	const Standard_Real y0,
	const std::shared_ptr<info>& theInfo
)
{
	hydStcLib::StbFun_IntgFun<HydStatic_StbFun> entity(*theFun, y0);
	NumAlg_AdaptiveInteg<hydStcLib::StbFun_IntgFun<HydStatic_StbFun>, true> 
		integration(entity, thePhi0, thePhi1, *theInfo);

	integration.Perform();
	Debug_If_Condition_Message(NOT integration.IsDone(), "the integration is not performed!");

	if (NOT theInfo->IsConverged())
	{
		FatalConvErrorIn("Standard_Real Area(Args...)", theInfo->MaxNbIterations(), theInfo->Tolerance())
			<< "the integration is not converged!" << endl
			<< abort(FatalError);
	}
	return theInfo->Result();
}