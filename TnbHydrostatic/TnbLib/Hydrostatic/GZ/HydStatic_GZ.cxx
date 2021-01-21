#include <HydStatic_GZ.hxx>

#include <MarineBase_Tools.hxx>
#include <HydStatic_GzQ.hxx>
#include <HydStatic_rArmCurve_Body.hxx>
#include <HydStatic_ArmCurveCreator_StbHeel.hxx>
#include <HydStatic_CrossCurves.hxx>
#include <HydStatic_CrsCurve.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>
#include <HydStatic_CmptLib.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

bool tnbLib::HydStatic_GZ::verbose = false;

tnbLib::HydStatic_GZ::HydStatic_GZ()
	: theKg_(marineLib::KG::null)
	, theDispv_(marineLib::DISPV::null)
{
	//- empty body
}

tnbLib::HydStatic_GZ::HydStatic_GZ
(
	const std::shared_ptr<HydStatic_CrossCurves>& theCrossCurves,
	const marineLib::KG& theKG,
	const marineLib::DISPV& theDispv
)
	: theCrossCurves_(theCrossCurves)
	, theKg_(theKG)
	, theDispv_(theDispv)
{
	//- empty body
}

tnbLib::HydStatic_GZ::HydStatic_GZ
(
	std::shared_ptr<HydStatic_CrossCurves>&& theCrossCurves,
	marineLib::KG&& theKG,
	marineLib::DISPV&& theDispv
)
	: theCrossCurves_(std::move(theCrossCurves))
	, theKg_(std::move(theKG))
	, theDispv_(std::move(theDispv))
{
	//- empty body
}

namespace tnbLib
{

	tnbLib::hydStcLib::CurveMakerType 
		RetrieveCurveType
		(
			const std::vector<std::shared_ptr<HydStatic_CrsCurve>>& theCurves
		)
	{
		if (theCurves.size() < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid data has been detected" << endl
				<< abort(FatalError);
		}
		const auto t = hydStcLib::RetrieveType(theCurves[0]);
		for (const auto& x : theCurves)
		{
			if (hydStcLib::RetrieveType(x) NOT_EQUAL t)
			{
				FatalErrorIn(FunctionSIG)
					<< "all of the cross-curves must be the same type" << endl
					<< abort(FatalError);
			}
		}
		return t;
	}
}

void tnbLib::HydStatic_GZ::Perform()
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Calculating GZ Curve ********" << endl;
		Info << endl;
	}

	if (NOT CrossCurves())
	{
		FatalErrorIn("void tnbLib::HydStatic_GZ::Perform()")
			<< "no crossCurves is loaded!" << endl
			<< abort(FatalError);
	}

	if (KG().IsNull())
	{
		FatalErrorIn("void tnbLib::HydStatic_GZ::Perform()")
			<< "no KG is specified!" << endl
			<< abort(FatalError);
	}

	if (DISPV().IsNull())
	{
		FatalErrorIn("void tnbLib::HydStatic_GZ::Perform()")
			<< "no DISPV is specified!" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		Info << " KG: " << KG()() << endl;
		Info << " Displacement: " << DISPV()() << endl;
		Info << endl;
	}

	const auto& crossCurves = *CrossCurves()->CrossCurves();
	const auto t = RetrieveCurveType(crossCurves.Curves());

	if (NOT INSIDE(DISPV()(), crossCurves.MinDispv(), crossCurves.MaxDispv()))
	{
		FatalErrorIn(FunctionSIG)
			<< "the displacement is not valid for the cross-curves diagram" << endl
			<< " - min. displacement: " << crossCurves.MinDispv() << endl
			<< " - max. displacement: " << crossCurves.MaxDispv() << endl
			<< " - displacement: " << DISPV()() << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		Info << " calculating lever arms..." << endl;
		Info << endl;
	}
	const auto leverArms = HydStatic_CmptLib::LeverArms(crossCurves.Curves(), DISPV()());

	if (verbose)
	{
		Info << " calculating GZ curve..." << endl;
		Info << endl;
	}
	const auto gzQ = HydStatic_CmptLib::GZ(leverArms, KG()());

	if (verbose)
	{
		Info << " calculating geometric curve..." << endl;
		Info << endl;
	}
	const auto curve = MarineBase_Tools::Curve(gzQ);

	const auto rArm = hydStcLib::MakeCurve<hydStcLib::rArmCurve_Body>(std::move(curve), t);

	ChangeRightingArm() = std::move(rArm);

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of Calculating GZ Curve ********" << endl;
		Info << endl;
	}
}

void tnbLib::HydStatic_GZ::LoadCrossCurves
(
	const std::shared_ptr<HydStatic_CrossCurves>& theCrossCurves
)
{
	theCrossCurves_ = theCrossCurves;
}

void tnbLib::HydStatic_GZ::LoadCrossCurves
(
	std::shared_ptr<HydStatic_CrossCurves>&& theCrossCurves
)
{
	theCrossCurves_ = std::move(theCrossCurves);
}

void tnbLib::HydStatic_GZ::SetKG
(
	const tnbLib::marineLib::KG& theKG
)
{
	theKg_ = theKG;
}

void tnbLib::HydStatic_GZ::SetKG
(
	marineLib::KG && theKG
)
{
	theKg_ = std::move(theKG);
}

void tnbLib::HydStatic_GZ::SetDispv
(
	const marineLib::DISPV & theV
)
{
	theDispv_ = theV;
}

void tnbLib::HydStatic_GZ::SetDispv
(
	marineLib::DISPV && theV
)
{
	theDispv_ = std::move(theV);
}