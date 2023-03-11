#include <Aft3d_Facet.hxx>

#include <Aft3d_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean
tnbLib::legLib::Aft3d_Facet::IsBoundary() const
{
	return Standard_False;
}

Standard_Boolean
tnbLib::legLib::Aft3d_Facet::IsInterior() const
{
	return Standard_False;
}

std::tuple<tnbLib::Pnt3d, tnbLib::Pnt3d, tnbLib::Pnt3d> 
tnbLib::legLib::Aft3d_Facet::RetrieveCoords() const
{
	auto [n0, n1, n2] = Nodes();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);
	auto p0 = n0->Coord();
	auto p1 = n1->Coord();
	auto p2 = n2->Coord();
	auto t = std::make_tuple(std::move(p0), std::move(p1), std::move(p2));
	return std::move(t);
}

std::tuple
<
	std::shared_ptr<tnbLib::legLib::Aft3d_Node>,
	std::shared_ptr<tnbLib::legLib::Aft3d_Node>,
	std::shared_ptr<tnbLib::legLib::Aft3d_Node>
> 
tnbLib::legLib::Aft3d_Facet::Nodes() const
{
	auto n0 = Node0();
	auto n1 = Node1();
	auto n2 = Node2();
	auto t = std::make_tuple(std::move(n0), std::move(n1), std::move(n1));
	return std::move(t);
}

std::tuple
<
	std::shared_ptr<tnbLib::legLib::Aft3d_Edge>,
	std::shared_ptr<tnbLib::legLib::Aft3d_Edge>,
	std::shared_ptr<tnbLib::legLib::Aft3d_Edge>
> 
tnbLib::legLib::Aft3d_Facet::Edges() const
{
	auto e0 = Edge0();
	auto e1 = Edge1();
	auto e2 = Edge2();
	auto t = std::make_tuple(std::move(e0), std::move(e1), std::move(e2));
	return std::move(t);
}