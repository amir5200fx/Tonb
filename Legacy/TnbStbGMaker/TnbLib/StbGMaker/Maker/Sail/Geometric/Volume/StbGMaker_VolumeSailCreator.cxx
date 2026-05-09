#include <StbGMaker_VolumeSailCreator.hxx>

#include <StbGMaker_SailWP.hxx>

std::shared_ptr<tnbLib::StbGMaker_WP> 
tnbLib::StbGMaker_VolumeSailCreator::MakeWP
(
	const Standard_Real x
) const
{
	auto wp = std::make_shared<StbGMaker_SailWP>(x);
	return std::move(wp);
}