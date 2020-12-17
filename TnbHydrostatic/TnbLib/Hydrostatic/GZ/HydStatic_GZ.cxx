#include <HydStatic_GZ.hxx>

#include <MarineBase_Tools.hxx>
#include <HydStatic_GzQ.hxx>
#include <HydStatic_rArmCurve_Body.hxx>
#include <HydStatic_ArmCurveCreator_StbHeel.hxx>
#include <HydStatic_CrossCurves.hxx>
#include <HydStatic_CmptLib.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

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

void tnbLib::HydStatic_GZ::Perform()
{
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

	const auto& crossCurves = *CrossCurves();

	const auto leverArms = HydStatic_CmptLib::LeverArms(crossCurves.CrossCurves(), DISPV()());
	const auto gzQ = HydStatic_CmptLib::GZ(leverArms, KG()());

	const auto curve = MarineBase_Tools::Curve(gzQ);

	const auto rArm = 
		std::make_shared<hydStcLib::ArmCurveCreator_StbHeel<hydStcLib::rArmCurve_Body>>(curve);

	ChangeRightingArm() = std::move(rArm);

	Change_IsDone() = Standard_True;
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