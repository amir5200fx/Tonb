#include <HydStatic_HullShape.hxx>

void tnbLib::HydStatic_HullShape::SetHull
(
	const std::shared_ptr<marineLib::Model_Hull>& theHull
)
{
	theHull_ = theHull;
}

void tnbLib::HydStatic_HullShape::SetHull
(
	std::shared_ptr<marineLib::Model_Hull>&& theHull
)
{
	theHull_ = std::move(theHull);
}

void tnbLib::HydStatic_HullShape::SetCrossCurves
(
	const std::shared_ptr<HydStatic_CrsCurvesGraph>& theCross
)
{
	theCross_ = theCross;
}

void tnbLib::HydStatic_HullShape::SetCrossCurves
(
	std::shared_ptr<HydStatic_CrsCurvesGraph>&& theCross
)
{
	theCross_ = std::move(theCross);
}

void tnbLib::HydStatic_HullShape::SetDispv
(
	const marineLib::DISPV & theV
)
{
	theDispv_ = theV;
}

void tnbLib::HydStatic_HullShape::SetDispv
(
	marineLib::DISPV && theV
)
{
	theDispv_ = std::move(theV);
}