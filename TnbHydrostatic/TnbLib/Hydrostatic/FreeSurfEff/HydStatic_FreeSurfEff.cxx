#include <HydStatic_FreeSurfEff.hxx>

#include <MarineBase_Tools.hxx>
#include <HydStatic_rArmCurve_FSLq.hxx>
#include <HydStatic_CurveMaker.hxx>
#include <HydStatic_CrsCurve.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>
#include <HydStatic_CmptLib.hxx>
#include <HydStatic_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

bool tnbLib::HydStatic_FreeSurfEff::verbose = false;

tnbLib::HydStatic_FreeSurfEff::HydStatic_FreeSurfEff()
	: theShip_(marineLib::DISPV::null)
	, theTank_(marineLib::DISPV::null)
{
	// empty body
}

tnbLib::HydStatic_FreeSurfEff::HydStatic_FreeSurfEff
(
	const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCrossCurves,
	const marineLib::DISPV & theTank,
	const marineLib::DISPV & theShip
)
	: theCrossCurves_(theCrossCurves)
	, theShip_(theShip)
	, theTank_(theTank)
{
	// empty body
}

void tnbLib::HydStatic_FreeSurfEff::Perform()
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Calculating FSE Curve ********" << endl;
		Info << endl;
	}

	if (NOT CrossCurves())
	{
		FatalErrorIn("void tnbLib::HydStatic_FreeSurfEff::Perform()")
			<< "no cross-curves has been loaded!" << endl
			<< abort(FatalError);
	}

	if (ShipDispv().IsNull())
	{
		FatalErrorIn("void tnbLib::HydStatic_FreeSurfEff::Perform()")
			<< "no displacement has been specified for the ship!" << endl
			<< abort(FatalError);
	}

	if (TankDispv().IsNull())
	{
		FatalErrorIn("void tnbLib::HydStatic_FreeSurfEff::Perform()")
			<< "no displacement has been specified for the tank!" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		Info << " Tank Displacement: " << TankDispv()() << endl;
		Info << " Ship Displacement: " << ShipDispv()() << endl;
		Info << endl;
	}

	const auto& crossCurves = *CrossCurves();
	const auto t = crossCurves.CurveType();

	if (NOT INSIDE(TankDispv()(), crossCurves.MinDispv(), crossCurves.MaxDispv()))
	{
		FatalErrorIn(FunctionSIG)
			<< "the displacement is not valid for the cross-curves diagram" << endl
			<< " - min. displacement: " << crossCurves.MinDispv() << endl
			<< " - max. displacement: " << crossCurves.MaxDispv() << endl
			<< " - displacement: " << TankDispv()() << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		Info << " calculating lever arms..." << endl;
		Info << endl;
	}
	const auto leverArms = HydStatic_CmptLib::LeverArms(CrossCurves(), TankDispv()());

	if (verbose)
	{
		Info << " calculating GZ curve..." << endl;
		Info << endl;
	}
	const auto gzQ = HydStatic_CmptLib::FSE(leverArms, TankDispv(), ShipDispv());

	if (verbose)
	{
		Info << " calculating geometric curve..." << endl;
		Info << endl;
	}
	//const auto curve = MarineBase_Tools::Curve(gzQ);

	//const auto rArm = hydStcLib::MakeCurve<hydStcLib::rArmCurve_FSLq>(std::move(curve), t);
	const auto rArm = HydStatic_Tools::MakeRightCurve<hydStcLib::rArmCurve_FSLq>(gzQ, t);

	HydStatic_CmptLib::CalcParameters(rArm);

	ChangeRightingArm() = std::move(rArm);

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of Calculating GZ Curve ********" << endl;
		Info << endl;
	}
}

void tnbLib::HydStatic_FreeSurfEff::LoadCrossCurves
(
	const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCrossCurves
)
{
	theCrossCurves_ = theCrossCurves;
}

void tnbLib::HydStatic_FreeSurfEff::LoadCrossCurves
(
	std::shared_ptr<HydStatic_CrsCurvesGraph>&& theCrossCurves
)
{
	theCrossCurves_ = std::move(theCrossCurves);
}

void tnbLib::HydStatic_FreeSurfEff::SetTankDispv
(
	const marineLib::DISPV & theDispv
)
{
	theTank_ = theDispv;
}

void tnbLib::HydStatic_FreeSurfEff::SetTankDispv
(
	marineLib::DISPV && theDispv
)
{
	theTank_ = std::move(theDispv);
}

void tnbLib::HydStatic_FreeSurfEff::SetShipDispv
(
	const marineLib::DISPV & theDispv
)
{
	theShip_ = theDispv;
}

void tnbLib::HydStatic_FreeSurfEff::SetShipDispv
(
	marineLib::DISPV && theDispv
)
{
	theShip_ = std::move(theDispv);
}