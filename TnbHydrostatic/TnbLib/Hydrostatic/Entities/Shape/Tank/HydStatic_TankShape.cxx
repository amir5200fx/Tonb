#include <HydStatic_TankShape.hxx>

tnbLib::HydStatic_TankShape::HydStatic_TankShape
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

tnbLib::HydStatic_TankShape::HydStatic_TankShape
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

tnbLib::HydStatic_TankShape::HydStatic_TankShape
(
	const Standard_Integer theIndex,
	const word & theName,
	const std::shared_ptr<marineLib::Model_Tank>& theTank,
	const std::shared_ptr<HydStatic_FillCurve>& theFill,
	const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross
)
	: HydStatic_Shape(theIndex, theName)
	, theTank_(theTank)
	, theFill_(theFill)
	, theCross_(theCross)
{
	//- empty body
}