#include <Mesh3d_Element.hxx>

#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<>
	Mesh3d_Element::array4 Mesh3d_Element::InterpWeights(const Pnt3d& theCoord) const
	{
		Debug_Null_Pointer(Node0());
		Debug_Null_Pointer(Node1());
		Debug_Null_Pointer(Node2());
		Debug_Null_Pointer(Node3());

		const auto& node0 = *Node0();
		const auto& node1 = *Node1();
		const auto& node2 = *Node2();
		const auto& node3 = *Node3();

		/*std::cout << "coord: " << theCoord << std::endl;
		std::cout << "n0: " << node0.Coord() << std::endl;
		std::cout << "n1: " << node1.Coord() << std::endl;
		std::cout << "n2: " << node2.Coord() << std::endl;
		std::cout << "n3: " << node3.Coord() << std::endl;*/

		const auto v0 = Geo_Tools::Volume_cgal(theCoord, node2.Coord(), node1.Coord(), node3.Coord());
		const auto v1 = Geo_Tools::Volume_cgal(theCoord, node0.Coord(), node2.Coord(), node3.Coord());
		const auto v2 = Geo_Tools::Volume_cgal(theCoord, node1.Coord(), node0.Coord(), node3.Coord());
		const auto v3 = Geo_Tools::Volume_cgal(theCoord, node0.Coord(), node1.Coord(), node2.Coord());
		
#ifdef _DEBUG
		if (v0 < 0 OR v1 < 0 OR v2 < 0 OR v3 < 0)
		{
			FatalErrorIn(FunctionSIG)
				<< "Inverse element has been detected!" << endl
				<< " - V0 = " << v0 << endl
				<< " - V1 = " << v1 << endl
				<< " - V2 = " << v2 << endl
				<< " - V3 = " << v3 << endl
				<< abort(FatalError);
		}
#endif // _DEBUG
		auto t = array4{ v0,v1,v2,v3 };
		return std::move(t);
	}
}

template<>
std::tuple<tnbLib::Pnt3d, tnbLib::Pnt3d, tnbLib::Pnt3d, tnbLib::Pnt3d> 
tnbLib::Mesh3d_Element::RetrieveCoords() const
{
	Debug_Null_Pointer(Node0());
	Debug_Null_Pointer(Node1());
	Debug_Null_Pointer(Node2());
	Debug_Null_Pointer(Node3());

	auto p0 = Node0()->Coord();
	auto p1 = Node1()->Coord();
	auto p2 = Node2()->Coord();
	auto p3 = Node3()->Coord();

	auto t = std::make_tuple(std::move(p0), std::move(p1), std::move(p2), std::move(p3));
	return std::move(t);
}