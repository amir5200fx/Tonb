#include <Marine_CmptLib.hxx>

#include <Pnt3d.hxx>
#include <Entity2d_Box.hxx>
#include <Cad2d_CmptLib.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_BaseLine.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_WaterTools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Ax1.hxx>

std::tuple<tnbLib::marineLib::LOA, tnbLib::marineLib::B, tnbLib::marineLib::D>
tnbLib::Marine_CmptLib::CalcBasicDim
(
	const Marine_Body & theBody
)
{
	const auto& sections = theBody.Sections();
	auto b = Marine_SectTools::BoundingBox(sections);

	const auto zmin = b.P0().Z();
	const auto& mid = sections[sections.size() / 2];
	Debug_Null_Pointer(mid);

	const auto b2 = mid->BoundingBox();

	const auto d = b2.P1().Y() - zmin;

	const auto[dx, dy, dz] = b.Length();

	marineLib::LOA loa(dx);
	marineLib::B bd(dy);
	marineLib::D df(d);

	auto t = std::make_tuple(std::move(loa), std::move(bd), std::move(df));
	return std::move(t);
}

tnbLib::marineLib::D 
tnbLib::Marine_CmptLib::SpecifyD
(
	const Standard_Real theD
)
{
	marineLib::D param(theD);
	return std::move(param);
}

tnbLib::marineLib::APP 
tnbLib::Marine_CmptLib::CalcAPP
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& awl = Marine_WaterLib::AWL(theBody);
	if (awl IS_EQUAL Marine_CmpSection::null)
	{
		FatalErrorIn("marineLib::APP CalcAPP(const Marine_WettedBody& theBody)")
			<< "failed to detect the AWL section" << endl
			<< abort(FatalError);
	}
	marineLib::APP param(awl->X());
	return std::move(param);
}

tnbLib::marineLib::FPP 
tnbLib::Marine_CmptLib::CalcFPP
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& fwl = Marine_WaterLib::FWL(theBody);
	if (fwl IS_EQUAL Marine_CmpSection::null)
	{
		FatalErrorIn("marineLib::FPP CalcFPP(const Marine_WettedBody& theBody)")
			<< "failed to detect the FWL section" << endl
			<< abort(FatalError);
	}
	marineLib::FPP param(fwl->X());
	return std::move(param);
}

tnbLib::marineLib::MPP 
tnbLib::Marine_CmptLib::CalcMPP
(
	const marineLib::APP & theApp, 
	const marineLib::FPP & theFpp
)
{
	marineLib::MPP param(MEAN(theApp(), theFpp()));
	return std::move(param);
}

tnbLib::marineLib::LWL 
tnbLib::Marine_CmptLib::CalcLWL
(
	const std::shared_ptr<marineLib::Body_Wetted>& theBody
)
{
	Debug_Null_Pointer(theBody);
	if (theBody->HasWaterSection())
	{
		auto wetted = std::dynamic_pointer_cast<marineLib::Body_WettedS>(theBody);
		Debug_Null_Pointer(wetted);

		auto lwl = CalcLWL(*wetted);
		return std::move(lwl);
	}
	else
	{
		auto lwl = CalcLWL(*theBody);
		return std::move(lwl);
	}
}

tnbLib::marineLib::LWL 
tnbLib::Marine_CmptLib::CalcLWL
(
	const marineLib::Body_WettedS & theBody
)
{
	const auto& wlSect = theBody.WL();
	if (NOT wlSect)
	{
		FatalErrorIn("marineLib::LWL CalcLWL(const Marine_WettedBody& theBody)")
			<< "failed to find water plane" << endl
			<< abort(FatalError);
	}

	const auto b = wlSect->BoundingBox();
	const auto[dx, dy] = b.Length();
	marineLib::LWL param(dx);
	return std::move(param);
}

tnbLib::marineLib::LWL 
tnbLib::Marine_CmptLib::CalcLWL
(
	const marineLib::Body_Wetted& theBody
)
{
	std::vector<std::shared_ptr<Marine_CmpSection>> sections;
	for (const auto& x : theBody.Sections())
	{
		Debug_Null_Pointer(x);
		auto onWaters = Marine_WaterTools::RetrieveNonDeepWLs(*x);

		if (onWaters.size())
		{
			sections.push_back(x);
		}
	}

	const auto b = Marine_SectTools::BoundingBox(sections);
	const auto[dx, dy, dz] = b.Length();
	marineLib::LWL param(dx);
	return std::move(param);
}

tnbLib::marineLib::BWL 
tnbLib::Marine_CmptLib::CalcBWL
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& sections = theBody.Sections();

	auto iter = sections.begin();
	const auto& x = *iter;
	Debug_Null_Pointer(x);

	auto bmax = MarineBase_Tools::CalcBWL(*x);

	iter++;
	while (iter NOT_EQUAL sections.end())
	{
		const auto& x = *iter;
		Debug_Null_Pointer(x);

		bmax = std::max(bmax, MarineBase_Tools::CalcBWL(*x));
		iter++;
	}
	marineLib::BWL param(bmax);
	return std::move(param);
}

tnbLib::marineLib::APP
tnbLib::Marine_CmptLib::CalcAPP
(
	const gp_Ax1 & theAx
)
{
	const auto& loc = theAx.Location();
	marineLib::APP param(loc.X());
	return std::move(param);
}

tnbLib::marineLib::FWL 
tnbLib::Marine_CmptLib::CalcFWL
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& fwl = Marine_WaterLib::FWL(theBody);
	if (fwl IS_EQUAL Marine_CmpSection::null)
	{
		FatalErrorIn("marineLib::FWL CalcFWL(const Marine_WettedBody& theBody)")
			<< "failed to detect the FWL section" << endl
			<< abort(FatalError);
	}
	marineLib::FWL param(fwl->X());
	return std::move(param);
}

tnbLib::marineLib::AWL 
tnbLib::Marine_CmptLib::CalcAWL
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& awl = Marine_WaterLib::AWL(theBody);
	if (awl IS_EQUAL Marine_CmpSection::null)
	{
		FatalErrorIn("marineLib::AWL CalcAWL(const Marine_WettedBody& theBody)")
			<< "failed to detect the AWL section" << endl
			<< abort(FatalError);
	}
	marineLib::AWL param(awl->X());
	return std::move(param);
}

tnbLib::marineLib::FUW 
tnbLib::Marine_CmptLib::CalcFUW
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& fuw = Marine_WaterLib::FUW(theBody);
	if (fuw IS_EQUAL Marine_CmpSection::null)
	{
		FatalErrorIn("marineLib::FUW CalcFUW(const Marine_WettedBody& theBody)")
			<< "failed to detect the FUW section" << endl
			<< abort(FatalError);
	}
	marineLib::FUW param(fuw->X());
	return std::move(param);
}

tnbLib::marineLib::AUW 
tnbLib::Marine_CmptLib::CalcAUW
(
	const marineLib::Body_Wetted& theBody
)
{
	const auto& auw = Marine_WaterLib::AUW(theBody);
	if (auw IS_EQUAL Marine_CmpSection::null)
	{
		FatalErrorIn("marineLib::AUW CalcAUW(const Marine_WettedBody& theBody)")
			<< "failed to detect the AUW section" << endl
			<< abort(FatalError);
	}
	marineLib::AUW param(auw->X());
	return std::move(param);
}

tnbLib::marineLib::LOS 
tnbLib::Marine_CmptLib::CalcLOS
(
	const marineLib::AUW & theAuw, 
	const marineLib::FUW & theFuw
)
{
	const auto los = theFuw() - theAuw();
	if (los <= gp::Resolution())
	{
		FatalErrorIn("marineLib::LOS CalcLOS(const marineLib::AUW& theAuw, const marineLib::FUW& theFuw)")
			<< "invalid los length: " << los << endl
			<< abort(FatalError);
	}
	marineLib::LOS param(los);
	return std::move(param);
}

tnbLib::marineLib::LPP 
tnbLib::Marine_CmptLib::CalcLPP
(
	const marineLib::APP & theAft,
	const marineLib::FPP & theFp
)
{
	const auto lpp = theFp() - theAft();
	if (lpp <= gp::Resolution())
	{
		FatalErrorIn("marineLib::LPP CalcLPP(const marineLib::APP& theAft, const marineLib::FPP& theFp)")
			<< "invalid lpp: " << lpp << endl
			<< abort(FatalError);
	}
	marineLib::LPP param(lpp);
	return std::move(param);
}



tnbLib::marineLib::LCF
tnbLib::Marine_CmptLib::CalcLCF
(
	const marineLib::Body_Wetted& theBody,
	const Standard_Real x0,
	const std::shared_ptr<info>& theInfo
)
{
	auto areaQ = MarineBase_Tools::CalcWaterPlaneArea(theBody.Sections(), theInfo);
	auto curve = MarineBase_Tools::Curve(areaQ);
	Debug_Null_Pointer(curve);

	auto product = Cad2d_CmptLib::xCentreProductArea(curve, theInfo);
	auto area = Cad2d_CmptLib::AreaUnderCurve(curve, 0, theInfo);

	marineLib::LCF param(product / area);
	return std::move(param);
}

tnbLib::marineLib::LCB
tnbLib::Marine_CmptLib::CalcLCB
(
	const marineLib::Body_Wetted& theBody,
	const Standard_Real x0,
	const std::shared_ptr<info>& theInfo
)
{
	auto volQ = MarineBase_Tools::CalcVolume(theBody.Sections(), theInfo);
	auto curve = MarineBase_Tools::Curve(volQ);
	Debug_Null_Pointer(curve);

	auto product = Cad2d_CmptLib::xCentreProductArea(curve, theInfo);
	auto area = Cad2d_CmptLib::AreaUnderCurve(curve, 0, theInfo);

	marineLib::LCB param(product / area);
	return std::move(param);
}

tnbLib::marineLib::DISPV
tnbLib::Marine_CmptLib::CalcDISPV
(
	const marineLib::Body_Wetted& theBody,
	const std::shared_ptr<info>& theInfo
)
{
	auto volQ = MarineBase_Tools::CalcVolume(theBody.Sections(), theInfo);
	auto vol = MarineBase_Tools::CalcArea(volQ, theInfo);
	marineLib::DISPV param(vol);
	return std::move(param);
}

tnbLib::marineLib::BM
tnbLib::Marine_CmptLib::CalcBM
(
	const Marine_CmpSection & theWPlane,
	const Standard_Real yc, 
	const marineLib::DISPV& theVolume,
	const std::shared_ptr<info>& theInfo
)
{
	if (theVolume() <= gp::Resolution())
	{
		FatalErrorIn("Standard_Real CalcBM(const Marine_CmpSection& theWPlane, const Standard_Real yc, const Standard_Real theVolume, const std::shared_ptr<info>& theInfo)")
			<< "the volume of the underwater body is zero" << endl
			<< abort(FatalError);
	}
	auto ix = MarineBase_Tools::CalcIx(theWPlane, yc, theInfo);
	marineLib::BM param(ix / theVolume());
	return std::move(param);
}

tnbLib::marineLib::BML
tnbLib::Marine_CmptLib::CalcBML
(
	const Marine_CmpSection & theWPlane, 
	const Standard_Real xc,
	const marineLib::DISPV& theVolume,
	const std::shared_ptr<info>& theInfo
)
{
	if (theVolume() <= gp::Resolution())
	{
		FatalErrorIn("Standard_Real CalcBML(const Marine_CmpSection& theWPlane, const Standard_Real xc, const Standard_Real theVolume, const std::shared_ptr<info>& theInfo)")
			<< "the volume of the underwater body is zero" << endl
			<< abort(FatalError);
	}
	auto iy = MarineBase_Tools::CalcIy(theWPlane, xc, theInfo);
	marineLib::BML param(iy / theVolume());
	return std::move(param);
}

//tnbLib::marineLib::TM 
//tnbLib::Marine_CmptLib::CalcTM
//(
//	const Marine_WettedBody & theBody
//)
//{
//	Debug_Null_Pointer(theBody.Mid());
//	const auto& mid = *theBody.Mid();
//
//	const auto b = mid.BoundingBox();
//	const auto[dx, dy] = b.Length();
//
//	marineLib::TM param(dy);
//	return std::move(param);
//}

tnbLib::marineLib::AM 
tnbLib::Marine_CmptLib::CalcAM
(
	const marineLib::Body_Wetted& theBody,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theBody.Mid());
	const auto& mid = *theBody.Mid();

	const auto area = MarineBase_Tools::CalcArea(mid, theInfo);
	marineLib::AM param(area);
	return std::move(param);
}

tnbLib::marineLib::KB
tnbLib::Marine_CmptLib::CalcKB
(
	const marineLib::Body_Wetted& theBody,
	const Marine_BaseLine & theBase,
	const std::shared_ptr<info>& theInfo
)
{
	const auto& loc = theBase.BaseLine().Location();

	Standard_Real sumA = 0;
	Standard_Real product = 0;
	for (const auto& x : theBody.Sections())
	{
		Debug_Null_Pointer(x);

		auto zb = MarineBase_Tools::CalcYCentre(*x, theInfo);
		auto area = MarineBase_Tools::CalcArea(*x, theInfo);
		
		product += zb * area;
		sumA += area;
	}

	const auto zbar = product / sumA;
	marineLib::KB param(zbar - loc.Z());
	return std::move(param);
}

tnbLib::marineLib::MCT 
tnbLib::Marine_CmptLib::CalcMCT
(
	const marineLib::BML& theBML,
	const marineLib::DISPV& theVolume, 
	const marineLib::LPP& theLpp
)
{
	if (theVolume() <= gp::Resolution())
	{
		FatalErrorIn("Standard_Real CalcMCT(const Standard_Real theBML, const Standard_Real theVolume, const Standard_Real theLpp)")
			<< "Invalid value of the Volume: " << theVolume() << endl
			<< abort(FatalError);
	}

	if (theLpp() <= gp::Resolution())
	{
		FatalErrorIn("Standard_Real CalcMCT(const Standard_Real theBML, const Standard_Real theVolume, const Standard_Real theLpp)")
			<< "Invalid value of the Lpp: " << theLpp() << endl
			<< abort(FatalError);
	}

	if (theBML() <= gp::Resolution())
	{
		FatalErrorIn("Standard_Real CalcMCT(const Standard_Real theBML, const Standard_Real theVolume, const Standard_Real theLpp)")
			<< "Invalid value of the BML: " << theBML() << endl
			<< abort(FatalError);
	}

	marineLib::MCT param(theVolume() * theBML() / theLpp());
	return std::move(param);
}

tnbLib::marineLib::AW
tnbLib::Marine_CmptLib::CalcAW
(
	const marineLib::Body_Wetted& theBody,
	const std::shared_ptr<info>& theInfo
)
{
	auto areaQ = MarineBase_Tools::CalcWaterPlaneArea(theBody.Sections(), theInfo);
	auto area = MarineBase_Tools::CalcArea(areaQ, theInfo);
	marineLib::AW param(area);
	return std::move(param);
}

tnbLib::marineLib::AW
tnbLib::Marine_CmptLib::CalcAW
(
	const Marine_CmpSection & theWPlane,
	const std::shared_ptr<info>& theInfo
)
{
	marineLib::AW param(MarineBase_Tools::CalcArea(theWPlane, theInfo));
	return std::move(param);
}

tnbLib::marineLib::CB 
tnbLib::Marine_CmptLib::CalcCB
(
	const marineLib::DISPV & theVol, 
	const marineLib::LPP & theLpp,
	const marineLib::BWL & theB,
	const marineLib::TM & theTm
)
{
	marineLib::CB param(theVol() / (theLpp()*theB()*theTm()));
	return std::move(param);
}

tnbLib::marineLib::CWL
tnbLib::Marine_CmptLib::CalcCWL
(
	const marineLib::AW & theAw,
	const marineLib::LWL & theLwl, 
	const marineLib::BWL & theB
)
{
	marineLib::CWL param(theAw() / (theLwl()*theB()));
	return std::move(param);
}

tnbLib::marineLib::CM
tnbLib::Marine_CmptLib::CalcCM
(
	const marineLib::AM & theAm, 
	const marineLib::BWL & theB,
	const marineLib::TM & theTm
)
{
	marineLib::CM param(theAm() / (theB()*theTm()));
	return std::move(param);
}

tnbLib::marineLib::CP 
tnbLib::Marine_CmptLib::CalcCP
(
	const marineLib::DISPV & theVol,
	const marineLib::AM & theAm,
	const marineLib::LWL & theLwl
)
{
	marineLib::CP param(theVol() / (theAm()*theLwl()));
	return std::move(param);
}

tnbLib::marineLib::CVP 
tnbLib::Marine_CmptLib::CalcCVP
(
	const marineLib::DISPV & theVol,
	const marineLib::AW & theAw,
	const marineLib::TM & theTm
)
{
	marineLib::CVP param(theVol() / (theAw()*theTm()));
	return std::move(param);
}