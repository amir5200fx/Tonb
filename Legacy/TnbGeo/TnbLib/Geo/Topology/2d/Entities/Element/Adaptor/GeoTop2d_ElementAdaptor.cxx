#include <GeoTop2d_ElementAdaptor.hxx>

std::shared_ptr<tnbLib::GeoTop2d_Element>
tnbLib::GeoTop2d_ElementAdaptor::Neighbor0() const
{
	auto elm = std::get<0>(Neighbors()).lock();
	return std::move(elm);
}

std::shared_ptr<tnbLib::GeoTop2d_Element>
tnbLib::GeoTop2d_ElementAdaptor::Neighbor1() const
{
	auto elm = std::get<1>(Neighbors()).lock();
	return std::move(elm);
}

std::shared_ptr<tnbLib::GeoTop2d_Element>
tnbLib::GeoTop2d_ElementAdaptor::Neighbor2() const
{
	auto elm = std::get<2>(Neighbors()).lock();
	return std::move(elm);
}

void tnbLib::GeoTop2d_ElementAdaptor::SetNeighbor0(const std::shared_ptr<GeoTop2d_Element>& theElement)
{
	std::get<0>(theNeighbors_) = theElement;
}

void tnbLib::GeoTop2d_ElementAdaptor::SetNeighbor1(const std::shared_ptr<GeoTop2d_Element>& theElement)
{
	std::get<1>(theNeighbors_) = theElement;
}

void tnbLib::GeoTop2d_ElementAdaptor::SetNeighbor2(const std::shared_ptr<GeoTop2d_Element>& theElement)
{
	std::get<2>(theNeighbors_) = theElement;
}