#pragma once
#include <Geo_Tools.hxx>
namespace tnbLib
{

	template<class BndType>
	Standard_Boolean Aft_BoundaryOfPlane_Base<BndType>::CheckWireOrientation
	(
		const std::vector<std::shared_ptr<BndType>>& theEdges,
		const Standard_Boolean ccw
	)
	{
		auto nodes = BndType::RetrieveNodes(BndType::UpCast(theEdges));
		if (nodes.size() < 3)
		{
			return Standard_False;
		}

		auto pts = BndType::bndNodeType::RetrieveGeometry(nodes);

		if (ccw)
		{
			return !Geo_Tools::IsCcwOrder_cgal(pts);
		}

		return Geo_Tools::IsCcwOrder_cgal(pts);
	}

	template<class BndType>
	Standard_Boolean Aft_BoundaryOfPlane_Base<BndType>::CheckWireNbPts
	(
		const std::vector<std::shared_ptr<BndType>>& theEdges
	)
	{
		return theEdges.size() < 3;
	}

	template<class BndType>
	Standard_Boolean Aft_BoundaryOfPlane_Base<BndType>::CheckSimplicity
	(
		const std::vector<std::shared_ptr<BndType>>& theEdges
	)
	{
		auto nodes = BndType::RetrieveNodes(BndType::UpCast(theEdges));
		if (nodes.size() < 3)
		{
			return Standard_False;
		}

		auto pts = BndType::bndNodeType::RetrieveGeometry(nodes);

		return !Geo_Tools::IsSimple_cgal(pts);
	}
}