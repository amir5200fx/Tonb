#include <Aft3d_SizeFun_Uniform.hxx>

tnbLib::legLib::Aft3d_SizeFun_Uniform::Aft3d_SizeFun_Uniform(std::shared_ptr<Domain> theDomain, Standard_Real theValue)
	: Aft3d_SizeFun(theDomain)
	, theValue_(theValue)
{
	// Empty body
}

Standard_Real tnbLib::legLib::Aft3d_SizeFun_Uniform::Value(const Pnt3d& /*thePnt*/) const
{
	return theValue_;
}
