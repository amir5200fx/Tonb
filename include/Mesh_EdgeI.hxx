#pragma once
#include <Geo_Tools.hxx>
template<class EdgeTraits>
inline Standard_Boolean tnbLib::Mesh_Edge<EdgeTraits>::IsBoundary() const
{
	return Standard_False;
}

namespace tnbLib
{

	template<class EdgeTraits>
	Standard_Real Mesh_Edge<EdgeTraits>::CalcDistance(const Point & theCoord) const
	{
		return Geo_Tools::Distance_cgal(theCoord, Node0()->Coord(), Node1()->Coord());
	}

	template<class EdgeTraits>
	Standard_Real Mesh_Edge<EdgeTraits>::CalcSquareDistance(const Point & theCoord) const
	{
		return Geo_Tools::SquareDistance_cgal(theCoord, Node0()->Coord(), Node1()->Coord());
	}

	template<class EdgeTraits>
	Standard_Boolean Mesh_Edge<EdgeTraits>::IsLess
	(
		const std::weak_ptr<Mesh_Edge>& theEdge0,
		const std::weak_ptr<Mesh_Edge>& theEdge1
	)
	{
		Debug_Null_Pointer(theEdge0.lock());
		Debug_Null_Pointer(theEdge1.lock());
		return theEdge0.lock()->Index() < theEdge1.lock()->Index();
	}

	template<class EdgeTraits>
	Standard_Boolean Mesh_Edge<EdgeTraits>::IsLess
	(
		const std::shared_ptr<Mesh_Edge>& theEdge0, 
		const std::shared_ptr<Mesh_Edge>& theEdge1
	)
	{
		Debug_Null_Pointer(theEdge0);
		Debug_Null_Pointer(theEdge1);
		return theEdge0->Index() < theEdge1->Index();
	}
}