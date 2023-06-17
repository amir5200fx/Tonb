#include <Aft3d_Element.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::legLib::Aft3d_Element::OppositeVertexIndex
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
) const
{
	for (Standard_Integer i = 0; i < 4; i++)
	{
		if (theFacets_.at(i) IS_EQUAL theFacet)
		{
			return i;
		}
	}
	FatalErrorIn(FunctionSIG)
		<< "the face doesn't belong to the current element." << endl
		<< abort(FatalError);
	return -1;
}

std::tuple
<
	std::shared_ptr<tnbLib::legLib::Aft3d_Node>, 
	std::shared_ptr<tnbLib::legLib::Aft3d_Node>,
	std::shared_ptr<tnbLib::legLib::Aft3d_Node>,
	std::shared_ptr<tnbLib::legLib::Aft3d_Node>
> 
tnbLib::legLib::Aft3d_Element::Nodes() const
{
	auto t = std::make_tuple(Node0(), Node1(), Node2(), Node3());
	return std::move(t);
}

std::tuple
<
	std::shared_ptr<tnbLib::legLib::Aft3d_Edge>,
	std::shared_ptr<tnbLib::legLib::Aft3d_Edge>, 
	std::shared_ptr<tnbLib::legLib::Aft3d_Edge>, 
	std::shared_ptr<tnbLib::legLib::Aft3d_Edge>, 
	std::shared_ptr<tnbLib::legLib::Aft3d_Edge>, 
	std::shared_ptr<tnbLib::legLib::Aft3d_Edge>
> 
tnbLib::legLib::Aft3d_Element::Edges() const
{
	auto t = std::make_tuple(Edge0(), Edge1(), Edge2(), Edge3(), Edge4(), Edge5());
	return std::move(t);
}

std::tuple
<
	std::shared_ptr<tnbLib::legLib::Aft3d_Facet>,
	std::shared_ptr<tnbLib::legLib::Aft3d_Facet>,
	std::shared_ptr<tnbLib::legLib::Aft3d_Facet>, 
	std::shared_ptr<tnbLib::legLib::Aft3d_Facet>
> tnbLib::legLib::Aft3d_Element::Facets() const
{
	auto t = std::make_tuple(Facet0(), Facet1(), Facet2(), Facet3());
	return std::move(t);
}