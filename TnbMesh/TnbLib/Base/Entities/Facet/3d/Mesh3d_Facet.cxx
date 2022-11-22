#include <Mesh3d_Facet.hxx>

#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<>
	Standard_Boolean Mesh3d_Facet::IsLeftSide(const Pnt3d& theCoord) const
	{
		Debug_Null_Pointer(Node0());
		Debug_Null_Pointer(Node1());
		Debug_Null_Pointer(Node2());

		const auto& n0 = *Node0();
		const auto& n1 = *Node1();
		const auto& n2 = *Node2();

		/*std::cout << "left side? " << std::endl;
		std::cout << n0.Coord() << std::endl;
		std::cout << n1.Coord() << std::endl;
		std::cout << n2.Coord() << std::endl;

		std::cout << std::endl;
		std::cout << theCoord << std::endl;
		std::cout << std::endl;

		std::cout << (Geo_Tools::IsPointLeftFacet_Fast(theCoord, n0.Coord(), n1.Coord(), n2.Coord()) ? "YES" : "NO") << std::endl;
		std::cout << "---------------------" << std::endl;
		std::cout << std::endl;*/

		return Geo_Tools::IsPointLeftFacet_Fast(theCoord, n0.Coord(), n1.Coord(), n2.Coord());
	}

	template<>
	Standard_Boolean Mesh3d_Facet::IsRightSide(const Pnt3d& theCoord) const
	{
		Debug_Null_Pointer(Node0());
		Debug_Null_Pointer(Node1());
		Debug_Null_Pointer(Node2());

		const auto& n0 = *Node0();
		const auto& n1 = *Node1();
		const auto& n2 = *Node2();

		/*std::cout << "right side? " << std::endl;
		std::cout << n0.Coord() << std::endl;
		std::cout << n1.Coord() << std::endl;
		std::cout << n2.Coord() << std::endl;

		std::cout << std::endl;
		std::cout << theCoord << std::endl;
		std::cout << std::endl;

		std::cout << (Geo_Tools::IsPointRightFacet_Fast(theCoord, n0.Coord(), n1.Coord(), n2.Coord()) ? "YES" : "NO") << std::endl;
		std::cout << "---------------------" << std::endl;
		std::cout << std::endl;*/

		return Geo_Tools::IsPointRightFacet_Fast(theCoord, n0.Coord(), n1.Coord(), n2.Coord());
	}
}

template<>
std::tuple<tnbLib::Pnt3d, tnbLib::Pnt3d, tnbLib::Pnt3d> 
tnbLib::Mesh3d_Facet::RetrieveCoords() const
{
	Debug_Null_Pointer(Node0());
	Debug_Null_Pointer(Node1());
	Debug_Null_Pointer(Node2());

	auto p0 = Node0()->Coord();
	auto p1 = Node1()->Coord();
	auto p2 = Node2()->Coord();

	auto t = std::make_tuple(std::move(p0), std::move(p1), std::move(p2));
	return std::move(t);
}