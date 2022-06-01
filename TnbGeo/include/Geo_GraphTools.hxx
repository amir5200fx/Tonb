#pragma once
#ifndef _Geo_GraphTools_Header
#define _Geo_GraphTools_Header

#include <Geo2d_GraphFwd.hxx>
#include <Geo2d_GraphNodeFwd.hxx>
#include <Geo2d_GraphEdgeFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity_Connectivity.hxx>
#include <Geo_Module.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [5/29/2022 Amir]
	class Pnt2d;

	class Geo_GraphTools
	{

	public:

		static TnbGeo_EXPORT std::pair<Standard_Boolean, std::shared_ptr<Geo2d_GraphEdge>> 
			IsEdge
			(
				const std::shared_ptr<Geo2d_GraphNode>&,
				const std::shared_ptr<Geo2d_GraphNode>&
			);

		static TnbGeo_EXPORT std::vector<std::shared_ptr<Geo2d_GraphNode>> 
			GetNodes
			(
				const std::vector<Pnt2d>&
			);

		static TnbGeo_EXPORT std::vector<std::shared_ptr<Geo2d_GraphEdge>> 
			GetEdges
			(
				const std::vector<std::shared_ptr<Geo2d_GraphNode>>&, 
				const std::vector<connectivity::triple>& theIds
			);

		static TnbGeo_EXPORT std::shared_ptr<Geo2d_Graph> 
			GetGraph
			(
				const Entity2d_Triangulation&
			);

		static TnbGeo_EXPORT std::vector<std::shared_ptr<Geo2d_GraphNode>> 
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Geo2d_GraphEdge>>&
			);
	};
}

#endif // !_Geo_GraphTools_Header
