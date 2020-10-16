#include <SectPx_FixedKnots.hxx>

std::vector<Standard_Real> 
tnbLib::SectPx_FixedKnots::CreateKnots
(
	const std::vector<std::shared_ptr<SectPx_Coord>>& theCoords,
	const Standard_Integer degree
) const
{
	auto copy = theKnots_;
	return std::move(copy);
}