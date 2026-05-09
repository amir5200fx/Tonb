#include <StbGMaker_TankCreator.hxx>

#include <StbGMaker_TankWP.hxx>

std::shared_ptr<tnbLib::StbGMaker_WP>
tnbLib::StbGMaker_TankCreator::MakeWP
(
	const Standard_Real x
) const
{
	auto wp = std::make_shared<StbGMaker_TankWP>(x);
	return std::move(wp);
}