#include <GeoTop2d_EdgeAdaptor.hxx>

Standard_Boolean 
tnbLib::GeoTop2d_EdgeAdaptor::IsOnBoundary() const
{
	return !RightElement();
}

std::shared_ptr<tnbLib::GeoTop2d_Element> 
tnbLib::GeoTop2d_EdgeAdaptor::LeftElement() const
{
	auto elm = theLeft_.lock();
	return std::move(elm);
}

std::shared_ptr<tnbLib::GeoTop2d_Element> 
tnbLib::GeoTop2d_EdgeAdaptor::RightElement() const
{
	auto elm = theRight_.lock();
	return std::move(elm);
}