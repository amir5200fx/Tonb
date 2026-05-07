#include <StbGMaker_Tools.hxx>

#include <Geo_Tools.hxx>
#include <Cad2d_Modeler.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Body.hxx>
#include <StbGMaker_WP.hxx>
#include <StbGMaker_IntplSect.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>

Standard_Real
tnbLib::StbGMaker_Tools::MinX
(
	const Marine_Body & theBody
)
{
	Debug_Null_Pointer(theBody.Sections()[0]);
	return theBody.Sections()[0]->X();
}

Standard_Real 
tnbLib::StbGMaker_Tools::MaxX
(
	const Marine_Body & theBody
)
{
	Debug_Null_Pointer(theBody.Sections()[theBody.NbSections() - 1]);
	return theBody.Sections()[theBody.NbSections() - 1]->X();
}

gp_Pln 
tnbLib::StbGMaker_Tools::IntplPln
(
	const Standard_Real x,
	const std::shared_ptr<Marine_CmpSection>& theS0,
	const std::shared_ptr<Marine_CmpSection>& theS1
)
{
	CheckSameDirection
	(
		theS0, theS1,
		"gp_Pln IntplPln(const Standard_Real x"
		", const std::shared_ptr<Marine_CmpSection>& theS0"
		", const std::shared_ptr<Marine_CmpSection>& theS1)"
	);

	const auto& ax = theS0->CoordinateSystem();
	auto pln = gp_Pln(ax.Location(), ax.Direction());
	return std::move(pln);
}

std::shared_ptr<tnbLib::Marine_CmpSection> 
tnbLib::StbGMaker_Tools::IntplHullSection
(
	const gp_Pln & thePlane,
	const std::shared_ptr<Marine_CmpSection>& theS0,
	const std::shared_ptr<Marine_CmpSection>& theS1,
	const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl
)
{
	Debug_Null_Pointer(theIntrpl);

	theIntrpl->LoadSect0(theS0);
	theIntrpl->LoadSect1(theS1);

	theIntrpl->Perform(thePlane);
	Debug_If_Condition_Message(NOT theIntrpl->IsDone(), "the interpolation algorithm is not performed!");

	auto interpolated = theIntrpl->Interpolated();
	return std::move(interpolated);
}

//std::shared_ptr<tnbLib::Marine_CmpSection> 
//tnbLib::StbGMaker_Tools::FitTankSectionToHull
//(
//	const std::shared_ptr<Marine_CmpSection>& theSection,
//	const std::shared_ptr<Marine_CmpSection>& theSHull0, 
//	const std::shared_ptr<Marine_CmpSection>& theSHull1,
//	const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl
//)
//{
//	if (
//		NOT Marine_SectTools::SameDirection(*theSHull0, *theSHull1) 
//		OR NOT Marine_SectTools::SameDirection(*theSHull0, *theSection)
//		)
//	{
//		FatalErrorIn
//		(
//			"std::shared_ptr<Marine_CmpSection> "
//			"FitTankSectionToHull("
//									"const std::shared_ptr<Marine_CmpSection>& theSection,"
//									"const std::shared_ptr<Marine_CmpSection>& theSHull0, "
//									"const std::shared_ptr<Marine_CmpSection>& theSHull1, "
//									"const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl)"
//		)
//			<< "the sections are not int the same direction" << endl
//			<< abort(FatalError);
//	}
//
//	Debug_Null_Pointer(theSection);
//	auto pln = Marine_SectTools::gpPln(*theSection);
//
//	auto hullSection = IntplHullSection(pln, theSHull0, theSHull1, theIntrpl);
//	Debug_Null_Pointer(hullSection);
//
//
//}

namespace tnbLib
{
	static Standard_Real xValue(const std::shared_ptr<tnbLib::Marine_CmpSection>& theSect)
	{
		Debug_Null_Pointer(theSect);
		return theSect->X();
	}
}

std::tuple
<
	std::shared_ptr<tnbLib::Marine_CmpSection>,
	std::shared_ptr<tnbLib::Marine_CmpSection>
> 
tnbLib::StbGMaker_Tools::FindSpan
(
	const Standard_Real x, 
	const Marine_Body & theBody
)
{
#ifdef _DEBUG
	CheckOutsideBoundaries
	(x, theBody,
		"std::tuple<std::shared_ptr<Marine_CmpSection>, std::shared_ptr<Marine_CmpSection>>"
		"FindSpan(const Standard_Real x, const Marine_Body& theBody)"
	);
#endif // _DEBUG

	const auto span = Geo_Tools::FindSpan(x, theBody.Sections(), &xValue);
	
	const auto& sections = theBody.Sections();
	auto x0 = sections[span];
	auto x1 = sections[span + 1];

	auto t = std::make_tuple(std::move(x0), std::move(x1));
	return std::move(t);
}

//std::vector<std::shared_ptr<tnbLib::Pln_Wire>> 
//tnbLib::StbGMaker_Tools::OuterWires
//(
//	const std::shared_ptr<StbGMaker_WP>& theWp
//)
//{
//	Debug_Null_Pointer(theWp);
//	const auto& modeler = theWp->Modeler();
//	if (NOT modeler)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the WP has no modeler!" << endl
//			<< " - wp's index = " << theWp->Index() << endl
//			<< " - wp's name = " << theWp->Name() << endl
//			<< abort(FatalError);
//	}
//
//	
//}

//std::tuple
//<
//	std::shared_ptr<tnbLib::Marine_CmpSection>,
//	std::shared_ptr<tnbLib::Marine_CmpSection>
//> 
//tnbLib::StbGMaker_Tools::FindSpan
//(
//	const Standard_Real x, 
//	const StbGMaker_Hull & theHull
//)
//{
//	auto t = FindSpan(x, *theHull.Body());
//	return std::move(t);
//}

//std::shared_ptr<tnbLib::StbGMaker_Tank> 
//tnbLib::StbGMaker_Tools::FitTankToHull
//(
//	const StbGMaker_Tank & theTank,
//	const StbGMaker_Hull & theHull, 
//	const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl
//)
//{
//	if (NOT theTank.Body())
//	{
//		FatalErrorIn
//		(
//			"std::shared_ptr<StbGMaker_Tank>"
//			"FitTankToHull"
//			"(const StbGMaker_Tank& theTank"
//			", const StbGMaker_Hull& theHull"
//			", const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl)"
//		)
//			<< "the tank has no body!" << endl
//			<< abort(FatalError);
//	}
//
//	if (NOT theHull.Body())
//	{
//		FatalErrorIn
//		(
//			"std::shared_ptr<StbGMaker_Tank>"
//			"FitTankToHull"
//			"(const StbGMaker_Tank& theTank"
//			", const StbGMaker_Hull& theHull"
//			", const std::shared_ptr<StbGMaker_IntplSect>& theIntrpl)"
//		)
//			<< "the hull has no body!" << endl
//			<< abort(FatalError);
//	}
//
//	const auto& tankBody = *theTank.Body();
//	const auto& hullBody = *theHull.Body();
//
//	std::vector<std::shared_ptr<Marine_CmpSection>> sections;
//	sections.reserve(tankBody.NbSections());
//
//	for (const auto& x : tankBody.Sections())
//	{
//		Debug_Null_Pointer(x);
//		
//		auto[s0, s1] = FindSpan(x->X(), hullBody);
//		Debug_Null_Pointer(s0);
//		Debug_Null_Pointer(s1);
//
//		auto section = FitTankSectionToHull(x->X(), s0, s1, theIntrpl);
//		Debug_Null_Pointer(section);
//
//		sections.push_back(std::move(section));
//	}
//
//	auto newTankBody = std::make_shared<Marine_TankBody>();
//	Debug_Null_Pointer(newTankBody);
//
//	newTankBody->ChangeSections() = std::move(sections);
//	auto newTank = std::make_shared<StbGMaker_Tank>(std::move(newTankBody));
//	Debug_Null_Pointer(newTank);
//
//	return std::move(newTank);
//}

void tnbLib::StbGMaker_Tools::CheckOutsideBoundaries
(
	const Standard_Real x,
	const Marine_Body & theBody,
	const char * theFunName
)
{
	const auto xMin = MinX(theBody);
	const auto xMax = MaxX(theBody);

	if (NOT INSIDE(x, xMin, xMax))
	{
		FatalErrorIn(theFunName)
			<< "the x-value is exceeded the body's domain" << endl
			<< " x = " << x << endl
			<< abort(FatalError);
	}
}