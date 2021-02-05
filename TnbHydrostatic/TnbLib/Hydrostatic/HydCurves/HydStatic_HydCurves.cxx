#include <HydStatic_HydCurves.hxx>

#include <Cad2d_CmptLib.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_System.hxx>
#include <Marine_CmptLib.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_Water.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <Marine_MidSection.hxx>
#include <Marine_MidSectionApprox_Near.hxx>
#include <HydStatic_HydGphCurves.hxx>
#include <HydStatic_HydCurvesGraph.hxx>
#include <HydStatic_xDraft.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

size_t tnbLib::HydStatic_HydCurves::verbose(0);

const Standard_Real tnbLib::HydStatic_HydCurves::DEFAULT_RHOFW(1.0);
const Standard_Real tnbLib::HydStatic_HydCurves::DEFAULT_RHOSW(1.25);

namespace tnbLib
{

	static bool nullifyMidSect = false;
}

tnbLib::marineLib::TM 
tnbLib::HydStatic_HydCurves::CalcTM
(
	const std::shared_ptr<marineLib::Body_Wetted>& theBody,
	const std::shared_ptr<Marine_Wave>& theWave, 
	const marineLib::APP& theApp, 
	const marineLib::FPP& theFpp
)
{
	Debug_Null_Pointer(theBody);

	if (NOT theBody->Mid())
	{
		if (verbose)
		{
			Info << " no mid ship section has been found" << endl;
			Info << " attempting to construct a midship section..." << endl;
		}

		const auto& displacer = theBody->Displacer();
		Marine_MidSection midSect(displacer, theBody, theWave);
		if (displacer->ShapeType())
		{
			auto x = MEAN(theApp(), theFpp());
			midSect.ApplyAt(x);
		}
		else
		{
			marineLib::MidSectionApprox_Near approx;
			approx.LoadBody(displacer);

			approx.Perform(MEAN(theApp(), theFpp()));
			Debug_If_Condition_Message(NOT approx.IsDone(), "the approximate mid-section is not performed!");

			Debug_Null_Pointer(approx.Section());
			midSect.ApplyAt(approx.Section());
		}

		if (verbose)
		{
			Info << " midShip section is added to the wetted body, successfully!" << endl;
		}

		nullifyMidSect = true;
	}

	auto par = Marine_CmptLib::CalcTM(*theBody);

	return std::move(par);
}

tnbLib::marineLib::APP 
tnbLib::HydStatic_HydCurves::CalcAPP
(
	const Standard_Real theAxis
)
{
	marineLib::APP par(theAxis);
	return std::move(par);
}

tnbLib::marineLib::APP 
tnbLib::HydStatic_HydCurves::CalcAPP
(
	const std::shared_ptr<marineLib::Body_Wetted>& theBody
)
{
	const auto par = Marine_CmptLib::CalcAPP(*theBody);
	return std::move(par);
}

std::tuple
<
	tnbLib::marineLib::CB,
	tnbLib::marineLib::CM,
	tnbLib::marineLib::CP, 
	tnbLib::marineLib::CWL,
	tnbLib::marineLib::LCF,
	tnbLib::marineLib::LCB,
	tnbLib::marineLib::AW,
	tnbLib::marineLib::MCT, 
	tnbLib::marineLib::KML,
	tnbLib::marineLib::KM, 
	tnbLib::marineLib::KB,
	tnbLib::marineLib::DISPV
> 
tnbLib::HydStatic_HydCurves::CalcParameters
(
	const std::shared_ptr<marineLib::Body_Wetted>& theBody,
	const Marine_BaseLine& theBase,
	const std::shared_ptr<Marine_Wave>& theWave,
	const std::shared_ptr<info>& theInfo
)
{
	nullifyMidSect = false;

	marineLib::APP app;
	if (RudderAxis())
	{
		app = CalcAPP(RudderAxisLoc());
	}
	else
	{
		app = CalcAPP(theBody);
	}

	const auto& body = *theBody;

	auto fpp = Marine_CmptLib::CalcFPP(body);
	auto lpp = Marine_CmptLib::CalcLPP(app, fpp);
	auto bwl = Marine_CmptLib::CalcBWL(body);
	
	marineLib::LWL lwl;
	marineLib::AW aw;
	if (body.ShapeType())
	{
		auto shaped =
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>
			>(theBody);

		Debug_Null_Pointer(shaped);
		lwl = Marine_CmptLib::CalcLWL(*shaped);
		aw = Marine_CmptLib::CalcAW(*shaped->WL(), theInfo);
	}
	else
	{
		auto noShape =
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_noShape<marineLib::Body_Wetted>
			>(theBody);

		Debug_Null_Pointer(noShape);
		lwl = Marine_CmptLib::CalcLWL(*noShape);
		aw = Marine_CmptLib::CalcAW(body, theInfo);
	}

	auto tm = CalcTM(theBody, theWave, app, fpp);
	auto am = Marine_CmptLib::CalcAM(body, theInfo);

	auto volQ = MarineBase_Tools::CalcVolume(body.Sections(), theInfo);
	auto volCurve = MarineBase_Tools::Curve(volQ);

	marineLib::DISPV dispv(MarineBase_Tools::CalcArea(volQ, theInfo));
	if (dispv() <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid volume is detected!" << endl
			<< abort(FatalError);
	}

	auto cb = Marine_CmptLib::CalcCB(dispv, lpp, bwl, tm);
	auto cm = Marine_CmptLib::CalcCM(am, bwl, tm);
	auto cp = Marine_CmptLib::CalcCP(dispv, am, lwl);
	auto cwl = Marine_CmptLib::CalcCWL(aw, lwl, bwl);

	auto lcf = Marine_CmptLib::CalcLCF(body, 0, theInfo);
	auto tcf = Marine_CmptLib::CalcTCF(body, aw, 0, theInfo);

	auto xProduct = Cad2d_CmptLib::xCentreProductArea(volCurve, theInfo);
	marineLib::LCB lcb(xProduct / dispv());

	marineLib::BML bml;
	marineLib::BM bm;
	if (body.ShapeType())
	{
		auto shaped =
			std::dynamic_pointer_cast
			<
			marineLib::BodyConstructor_Shape<marineLib::Body_Wetted>
			>(theBody);

		Debug_Null_Pointer(shaped);
		bml = Marine_CmptLib::CalcBML(*shaped->WL(), lcf(), dispv, theInfo);
		bm = Marine_CmptLib::CalcBM(*shaped->WL(), tcf(), dispv, theInfo);
	}
	else
	{
		bml = Marine_CmptLib::CalcBML(body, lcf(), dispv, theInfo);
		bm = Marine_CmptLib::CalcBM(body, tcf(), dispv, theInfo);
	}

	auto mct = Marine_CmptLib::CalcMCT(bml, dispv, lpp);

	auto kb = Marine_CmptLib::CalcKB(body, dispv, theBase, theInfo);
	auto kml = Marine_CmptLib::CalcKML(kb, bml);
	auto km = Marine_CmptLib::CalcKM(kb, bm);

	if (nullifyMidSect)
	{
		//- remove the mid-section
		theBody->NullifyMidSection();
	}

	auto t = std::make_tuple
	(
		std::move(cb),
		std::move(cm), 
		std::move(cp),
		std::move(cwl),
		std::move(lcf),
		std::move(lcb), 
		std::move(aw), 
		std::move(mct),
		std::move(kml), 
		std::move(km), 
		std::move(kb),
		std::move(dispv)
	);
	return std::move(t);
}

void tnbLib::HydStatic_HydCurves::Perform()
{
	if (NOT Waters())
	{
		FatalErrorIn(FunctionSIG)
			<< "no water domain has been detected!" << endl
			<< abort(FatalError);
	}

	auto body = std::dynamic_pointer_cast<marineLib::Body_Displacer>(Waters()->Body());
	if (NOT body)
	{
		FatalErrorIn(FunctionSIG)
			<< "no displacer body is loaded!" << endl
			<< abort(FatalError);
	}

	const auto& base = body->BaseLine();

	const auto nbWaters = Waters()->Waters().size();
	std::vector<hydStcGphLib::xDraft> 
		xCb,
		xCm,
		xCp,
		xCwl,
		xLcf, 
		xLcb,
		xAw,
		xMct,
		xKml, 
		xKm, 
		xKb,
		xDispv,
		xDispsw,
		xDispfw;
	xCb.reserve(nbWaters - 1);
	xCm.reserve(nbWaters - 1);
	xCp.reserve(nbWaters - 1);
	xCwl.reserve(nbWaters - 1);
	xLcf.reserve(nbWaters - 1);
	xLcb.reserve(nbWaters - 1);
	xAw.reserve(nbWaters - 1);
	xMct.reserve(nbWaters - 1);
	xKml.reserve(nbWaters - 1);
	xKm.reserve(nbWaters - 1);
	xKb.reserve(nbWaters - 1);
	xDispv.reserve(nbWaters - 1);
	xDispsw.reserve(nbWaters - 1);
	xDispfw.reserve(nbWaters - 1);

	const auto& waters = Waters()->Waters();
	for (size_t i = 0; i < waters.size() - 1; i++)
	{
		const auto& x = waters[i];
		Debug_Null_Pointer(x);

		//const auto& loc = x->CoordinateSystem().Location();
		auto wetted = 
			std::dynamic_pointer_cast<marineLib::Body_Wetted>
			(
				Marine_BodyTools::WettedBody(body, x)
				);
		Debug_Null_Pointer(wetted);

		auto[cb, cm, cp, cwl, lcf, lcb, aw, mct, kml, km, kb, dispv] = 
			CalcParameters
			(
				wetted, base, 
				x->Wave(),
				sysLib::gl_marine_integration_info
			);

		auto cbi = hydStcGphLib::xDraft{ x->Z(),cb() };
		xCb.push_back(std::move(cbi));

		auto cmi = hydStcGphLib::xDraft{ x->Z(),cm() };
		xCm.push_back(std::move(cmi));

		auto cpi = hydStcGphLib::xDraft{ x->Z(),cp() };
		xCp.push_back(std::move(cpi));

		auto cwli = hydStcGphLib::xDraft{ x->Z(),cwl() };
		xCwl.push_back(std::move(cwli));

		auto lcfi = hydStcGphLib::xDraft{ x->Z(),lcf() };
		xLcf.push_back(std::move(lcfi));

		auto lcbi = hydStcGphLib::xDraft{ x->Z(),lcb() };
		xLcb.push_back(std::move(lcbi));

		auto awi = hydStcGphLib::xDraft{ x->Z(),aw() };
		xAw.push_back(std::move(awi));

		auto mcti = hydStcGphLib::xDraft{ x->Z(),mct() };
		xMct.push_back(std::move(mcti));

		auto kmli = hydStcGphLib::xDraft{ x->Z(),kml() };
		xKml.push_back(std::move(kmli));

		auto kmi = hydStcGphLib::xDraft{ x->Z(),km() };
		xKm.push_back(std::move(kmi));

		auto kbi = hydStcGphLib::xDraft{ x->Z(),kb() };
		xKb.push_back(std::move(kbi));

		auto dispvi = hydStcGphLib::xDraft{ x->Z(),dispv() };
		xDispv.push_back(std::move(dispvi));

		auto dispswi = hydStcGphLib::xDraft{ x->Z(), dispv()*(RhoSW() + DisplFactor()) };
		xDispsw.push_back(std::move(dispswi));

		auto dispfwi = hydStcGphLib::xDraft{ x->Z(), dispv()*(RhoFW() + DisplFactor()) };
		xDispfw.push_back(std::move(dispfwi));
	}

	std::vector<std::shared_ptr<HydStatic_HydGphCurve>> curves;
	curves.reserve(14);
	
	auto cbCurve = hydStcGphLib::CB::Curve(xCb);
	cbCurve->SetName("CB");
	auto cmCurve = hydStcGphLib::CM::Curve(xCm);
	cmCurve->SetName("CM");
	auto cpCurve = hydStcGphLib::CP::Curve(xCp);
	cpCurve->SetName("CP");
	auto cwlCurve = hydStcGphLib::CWL::Curve(xCwl);
	cwlCurve->SetName("CWL");
	auto lcfCurve = hydStcGphLib::LCF::Curve(xLcf);
	lcfCurve->SetName("LCF");
	auto lcbCurve = hydStcGphLib::LCB::Curve(xLcb);
	lcbCurve->SetName("LCB");
	auto awCurve = hydStcGphLib::AW::Curve(xAw);
	awCurve->SetName("AW");
	auto mctCurve = hydStcGphLib::MCT::Curve(xMct);
	mctCurve->SetName("MCT");
	auto kmlCurve = hydStcGphLib::KML::Curve(xKml);
	kmlCurve->SetName("KML");
	auto kmCurve = hydStcGphLib::KM::Curve(xKm);
	kmCurve->SetName("KM");
	auto kbCurve = hydStcGphLib::KB::Curve(xKb);
	kbCurve->SetName("KB");
	auto dispvCurve = hydStcGphLib::DISPV::Curve(xDispv);
	dispvCurve->SetName("DISPV");
	auto dispswCurve = hydStcGphLib::DISPV::Curve(xDispsw);
	dispswCurve->SetName("DISPSW");
	auto dispfwCurve = hydStcGphLib::DISPV::Curve(xDispfw);
	dispfwCurve->SetName("DISPFW");

	curves.push_back(std::move(cbCurve));
	curves.push_back(std::move(cmCurve));
	curves.push_back(std::move(cpCurve));
	curves.push_back(std::move(cwlCurve));
	curves.push_back(std::move(lcfCurve));
	curves.push_back(std::move(lcbCurve));
	curves.push_back(std::move(awCurve));
	curves.push_back(std::move(mctCurve));
	curves.push_back(std::move(kmlCurve));
	curves.push_back(std::move(kmCurve));
	curves.push_back(std::move(kbCurve));
	curves.push_back(std::move(dispvCurve));
	curves.push_back(std::move(dispfwCurve));
	curves.push_back(std::move(dispswCurve));

	auto & graph = GraphRef();

	graph = std::make_shared<HydStatic_HydCurvesGraph>(0, "Hydrostatic-Curves");
	graph->Perform(std::move(curves));
	Debug_If_Condition_Message(NOT graph->IsDone(), "the algorihm is not performed!");

	Change_IsDone() = Standard_True;
}

void tnbLib::HydStatic_HydCurves::SetRudderLocation(const Standard_Real x)
{
	RudderAxis_ = Standard_True;
	theRudderAxisLoc_ = x;
}