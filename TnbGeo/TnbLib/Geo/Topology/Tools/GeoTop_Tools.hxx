#pragma once
#ifndef _GeoTop_Tools_Header
#define _GeoTop_Tools_Header

#include <Geo_Module.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Entity_Connectivity.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [2/17/2023 Payvand]

	class GeoTop2d_Element;
	class GeoTop2d_Vertex;
	class Entity3d_TriangulationPatch;

	class GeoTop_Tools
	{

	public:

		static std::shared_ptr<Entity3d_Box> CalcBoundingBox(const std::vector<std::shared_ptr<GeoTop2d_Element>>&);

		static TnbGeo_EXPORT std::vector<std::shared_ptr<GeoTop2d_Vertex>> 
			MakeVertices(const std::vector<Pnt3d>&);
		static TnbGeo_EXPORT std::vector<std::shared_ptr<GeoTop2d_Element>> 
			MakeElements(const Entity3d_Triangulation&);
		static TnbGeo_EXPORT std::vector<std::shared_ptr<GeoTop2d_Element>>
			CalcTopology(const Entity3d_Triangulation&);

		static TnbGeo_EXPORT std::vector<std::shared_ptr<std::vector<connectivity::dual>>> 
			CalcBoundaries(const std::vector<std::shared_ptr<GeoTop2d_Element>>&);

		static TnbGeo_EXPORT void MakeEdges(const std::vector<std::shared_ptr<GeoTop2d_Element>>&);
		static TnbGeo_EXPORT void ConnectNodesAndElements(const std::vector<std::shared_ptr<GeoTop2d_Element>>&);
		static TnbGeo_EXPORT void ConnectElements(const std::vector<std::shared_ptr<GeoTop2d_Element>>&);
	};
}

#endif // !_GeoTop_Tools_Header
