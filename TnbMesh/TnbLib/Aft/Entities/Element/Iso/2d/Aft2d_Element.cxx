#include <Aft2d_Element.hxx>

#include <Aft2d_Node.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<>
	Mesh_Element<Aft2d_ElementTraits, Mesh_ElementType_Triangle2D>::array3 
		Mesh_Element<Aft2d_ElementTraits, Mesh_ElementType_Triangle2D>::InterpWeights(const Pnt2d& theCoord) const
	{
		Debug_Null_Pointer(Node0());
		Debug_Null_Pointer(Node1());
		Debug_Null_Pointer(Node2());

		const auto& node0 = *Node0();
		const auto& node1 = *Node1();
		const auto& node2 = *Node2();

		auto A1 = Geo_Tools::Area_cgal(node1.Coord(), node2.Coord(), theCoord);
		auto A2 = Geo_Tools::Area_cgal(node2.Coord(), node0.Coord(), theCoord);
		auto A3 = Geo_Tools::Area_cgal(node0.Coord(), node1.Coord(), theCoord);

#if _DEBUG
		if (A1 < 0 OR A2 < 0 OR A3 < 0)
		{
			FatalErrorIn(FunctionSIG)
				<< "Inverse element has been encountered!" << endl
				<< " - A1 = " << A1 << endl
				<< " - A2 = " << A2 << endl
				<< " - A3 = " << A3 << endl
				<< abort(FatalError);
		}
#endif

		array3 t;
		t[0] = A1;
		t[1] = A2;
		t[2] = A3;
		return std::move(t);
	}
}