#include <Aft3d_ElementAdaptor.hxx>

#include <Aft3d_Element.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::legLib::Aft3d_Element>
tnbLib::legLib::Aft3d_ElementAdaptor::Neighbor(const Standard_Integer theIndex) const
{
	auto elm = theNeighbors_.at(theIndex).lock();
	return std::move(elm);
}

std::shared_ptr<tnbLib::legLib::Aft3d_Element>
tnbLib::legLib::Aft3d_ElementAdaptor::Neighbor0() const
{
	auto elm = Neighbor(0);
	return std::move(elm);
}

std::shared_ptr<tnbLib::legLib::Aft3d_Element>
tnbLib::legLib::Aft3d_ElementAdaptor::Neighbor1() const
{
	auto elm = Neighbor(1);
	return std::move(elm);
}

std::shared_ptr<tnbLib::legLib::Aft3d_Element>
tnbLib::legLib::Aft3d_ElementAdaptor::Neighbor2() const
{
	auto elm = Neighbor(2);
	return std::move(elm);
}

std::shared_ptr<tnbLib::legLib::Aft3d_Element>
tnbLib::legLib::Aft3d_ElementAdaptor::Neighbor3() const
{
	auto elm = Neighbor(3);
	return std::move(elm);
}

void tnbLib::legLib::Aft3d_ElementAdaptor::SetNeighbor0
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	std::get<0>(theNeighbors_) = theElement;
}

void tnbLib::legLib::Aft3d_ElementAdaptor::SetNeighbor1
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	std::get<1>(theNeighbors_) = theElement;
}

void tnbLib::legLib::Aft3d_ElementAdaptor::SetNeighbor2
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	std::get<2>(theNeighbors_) = theElement;
}

void tnbLib::legLib::Aft3d_ElementAdaptor::SetNeighbor3
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	std::get<3>(theNeighbors_) = theElement;
}