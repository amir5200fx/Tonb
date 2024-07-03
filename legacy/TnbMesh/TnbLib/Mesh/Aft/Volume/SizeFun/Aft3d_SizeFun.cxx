#include <Aft3d_SizeFun.hxx>

tnbLib::legLib::Aft3d_SizeFun::Aft3d_SizeFun(std::shared_ptr<Domain> theDomain)
	: theDomain_(std::move(theDomain))
{
	// Empty body
}
