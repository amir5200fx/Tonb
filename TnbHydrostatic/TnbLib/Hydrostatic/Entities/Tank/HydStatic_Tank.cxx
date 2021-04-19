#include <HydStatic_Tank.hxx>

tnbLib::HydStatic_Tank::HydStatic_Tank
(
	const std::shared_ptr<marineLib::Model_Tank>& theTank,
	const std::shared_ptr<HydStatic_FillCurve>& theFill,
	const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross
)
	: theTank_(theTank)
	, theFill_(theFill)
	, theCross_(theCross)
{
	//- empty body
}

tnbLib::HydStatic_Tank::HydStatic_Tank
(
	std::shared_ptr<marineLib::Model_Tank>&& theTank, 
	std::shared_ptr<HydStatic_FillCurve>&& theFill,
	std::shared_ptr<HydStatic_CrsCurvesGraph>&& theCross
)
	: theTank_(std::move(theTank))
	, theFill_(std::move(theFill))
	, theCross_(std::move(theCross))
{
	//- empty body
}

tnbLib::HydStatic_Tank::HydStatic_Tank
(
	const Standard_Integer theIndex, 
	const word & theName,
	const std::shared_ptr<marineLib::Model_Tank>& theTank, 
	const std::shared_ptr<HydStatic_FillCurve>& theFill, 
	const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross
)
	: HydStatic_Entity(theIndex, theName)
	, theTank_(theTank)
	, theFill_(theFill)
	, theCross_(theCross)
{
	//- empty body
}