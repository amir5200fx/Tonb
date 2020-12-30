#include <StbGMaker_HullCreator.hxx>

#include <StbGMaker_HullWP.hxx>

std::shared_ptr<tnbLib::StbGMaker_WP> 
tnbLib::StbGMaker_HullCreator::MakeWP
(
	const Standard_Real x
) const
{
	auto wp = std::make_shared<StbGMaker_HullWP>(x);
	return std::move(wp);
}