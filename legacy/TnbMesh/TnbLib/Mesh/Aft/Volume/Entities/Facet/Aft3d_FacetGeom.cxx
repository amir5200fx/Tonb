#include <Aft3d_Facet.hxx>

#include <Aft3d_Node.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::legLib::Aft3d_Facet::Oriented(const Pnt3d& theCoord) const
{
	const auto& n0 = Node0();
	const auto& n1 = Node1();
	const auto& n2 = Node2();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);

	const auto& p0 = n0->Coord();
	const auto& p1 = n1->Coord();
	const auto& p2 = n2->Coord();
	return Geo_Tools::Oriented_cgal(theCoord, p0, p1, p2);
}

Standard_Real 
tnbLib::legLib::Aft3d_Facet::CalcDistance(const Pnt3d& theCoord) const
{
	const auto& n0 = Node0();
	const auto& n1 = Node1();
	const auto& n2 = Node2();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);

	const auto& p0 = n0->Coord();
	const auto& p1 = n1->Coord();
	const auto& p2 = n2->Coord();
	return Geo_Tools::Distance_cgal(theCoord, p0, p1, p2);
}

Standard_Real 
tnbLib::legLib::Aft3d_Facet::CalcSquareDistance(const Pnt3d& theCoord) const
{
	const auto& n0 = Node0();
	const auto& n1 = Node1();
	const auto& n2 = Node2();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);

	const auto& p0 = n0->Coord();
	const auto& p1 = n1->Coord();
	const auto& p2 = n2->Coord();
	return Geo_Tools::SquareDistance_cgal(theCoord, p0, p1, p2);
}

Standard_Real 
tnbLib::legLib::Aft3d_Facet::SearchRadius() const
{
	const auto& n0 = Node0();
	const auto& n1 = Node1();
	const auto& n2 = Node2();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);
	return std::max
	(
		n0->FrontSpecs().Radius(), 
		std::max(n1->FrontSpecs().Radius(), n2->FrontSpecs().Radius())
	);
}

Standard_Boolean 
tnbLib::legLib::Aft3d_Facet::IsRightSide
(
	const Pnt3d& theCoord
) const
{
	const auto& n0 = Node0();
	const auto& n1 = Node1();
	const auto& n2 = Node2();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);
	
	const auto& p0 = n0->Coord();
	const auto& p1 = n1->Coord();
	const auto& p2 = n2->Coord();
	return Geo_Tools::IsPointRightFacet_cgal(theCoord, p0, p1, p2);
}

Standard_Boolean
tnbLib::legLib::Aft3d_Facet::IsLeftSide
(
	const Pnt3d& theCoord
) const
{
	const auto& n0 = Node0();
	const auto& n1 = Node1();
	const auto& n2 = Node2();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);

	const auto& p0 = n0->Coord();
	const auto& p1 = n1->Coord();
	const auto& p2 = n2->Coord();
	return Geo_Tools::IsPointLeftFacet_cgal(theCoord, p0, p1, p2);
}

tnbLib::Pnt3d 
tnbLib::legLib::Aft3d_Facet::CalcCentre() const
{
	static const Standard_Real cte = 1.0 / 3.0;
	const auto& n0 = Node0();
	const auto& n1 = Node1();
	const auto& n2 = Node2();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);

	const auto& p0 = n0->Coord();
	const auto& p1 = n1->Coord();
	const auto& p2 = n2->Coord();
	auto pt = (p0 + p1 + p2) * cte;
	return std::move(pt);
}