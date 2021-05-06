#include <HydStatic_TankShape.hxx>

#include <HydStatic_FillCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real tnbLib::HydStatic_TankShape::DEFAULT_PERC_VALUE(0.5);

tnbLib::HydStatic_TankShape::HydStatic_TankShape
(
	const std::shared_ptr<marineLib::Model_Tank>& theTank,
	const std::shared_ptr<HydStatic_FillCurve>& theFill,
	const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross
)
	: theTank_(theTank)
	, theFill_(theFill)
	, theCross_(theCross)
	, thePerc_(DEFAULT_PERC_VALUE)
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
	, thePerc_(DEFAULT_PERC_VALUE)
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
	, thePerc_(DEFAULT_PERC_VALUE)
{
	//- empty body
}

Standard_Real 
tnbLib::HydStatic_TankShape::Capacity() const
{
	return theFill_->MaxVolume();
}

void tnbLib::HydStatic_TankShape::SetKG(const Standard_Real theKg)
{
	theKg_() = theKg;
}

void tnbLib::HydStatic_TankShape::SetFullnessPerc(const Standard_Real x)
{
	if (NOT INSIDE(x, 0, 1))
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid data: the fullness percentage must be between 0 and 1" << endl
			<< " - perc. value: " << x << endl
			<< abort(FatalError);
	}
	thePerc_ = x;
}