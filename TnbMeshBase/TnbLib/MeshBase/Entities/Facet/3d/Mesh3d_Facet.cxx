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

		return Geo_Tools::IsPointLeftFacet_cgal(theCoord, n0.Coord(), n1.Coord(), n2.Coord());
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

		return Geo_Tools::IsPointRightFacet_cgal(theCoord, n0.Coord(), n1.Coord(), n2.Coord());
	}
}