#include <SectPx_FixedKnots.hxx>

std::vector<Standard_Real> 
tnbLib::SectPx_FixedKnots::CreateKnots
(
	const std::vector<Pnt2d>& theCoords,
	const Standard_Integer degree
) const
{
	auto copy = theKnots_;
	return std::move(copy);
}