#pragma once
#ifndef _Voyage_Tools_Header
#define _Voyage_Tools_Header

#include <VoyageMesh_MetricPrcsrFwd.hxx>
#include <VoyageGeo_VelocityBackgroundFwd.hxx>
#include <Voyage_Module.hxx>
#include <GeoMesh2d_SingleBackgroundFwd.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity_Connectivity.hxx>
#include <Vec2d.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [7/21/2023 Payvand]
	class Voyage_MetricInfo;
	class VoyageMesh_Element;
	class VoyageWP_Net;
	class VoyageMesh_Edge;
	class VoyageMesh_Node;
	class VoyageGeo_Path2;
	class VoyageGeo_Earth;
	class Voyage_Edge;
	class Voyage_Node;
	class Cad_GeomSurface;
	class Pnt2d;
	class Vec2d;

	template<class Point, class Value>
	class Mesh_SetSourcesNode;

	class Voyage_Tools
	{

	public:

		static TnbVoyage_EXPORT std::shared_ptr<Entity2d_Box> 
			RetrieveDomain(const VoyageGeo_Earth&);

		static TnbVoyage_EXPORT std::vector<Pnt2d>
			RetrieveGeometry
			(
				const std::vector<std::shared_ptr<VoyageMesh_Node>>&
			);

		static TnbVoyage_EXPORT std::vector<Pnt3d>
			RetrieveGeometry3d
			(
				const std::vector<std::shared_ptr<VoyageMesh_Node>>&
			);

		static TnbVoyage_EXPORT std::vector<connectivity::triple>
			RetrieveTriangleConnectivities
			(
				const std::vector<std::shared_ptr<VoyageMesh_Node>>&, 
				const std::vector<std::shared_ptr<VoyageMesh_Element>>&
			);

		// the nodes are sorted based on their indices 
		// So the first node is departure and the last one is destination [7/21/2023 Payvand]
		static TnbVoyage_EXPORT std::vector<std::shared_ptr<Voyage_Node>> 
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Voyage_Edge>>&
			);

		static TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageMesh_Node>>
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<VoyageMesh_Element>>&
			);

		static TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageMesh_Node>>
			RetrieveTipNodes
			(
				const std::vector<std::shared_ptr<VoyageMesh_Element>>&
			);

		static std::vector<std::shared_ptr<VoyageMesh_Edge>> RetrieveRefEdges(const std::vector<std::shared_ptr<VoyageMesh_Element>>&);

		static TnbVoyage_EXPORT std::shared_ptr<Voyage_Node> 
			NeighborNode
			(
				const std::shared_ptr<Voyage_Node>& theCurrent, 
				const std::shared_ptr<Voyage_Edge>& theEdge
			);

		static TnbVoyage_EXPORT std::shared_ptr<Voyage_Edge> 
			RetrieveEdge
			(
				const std::shared_ptr<Voyage_Node>&,
				const std::shared_ptr<Voyage_Node>&
			);

		static TnbVoyage_EXPORT std::shared_ptr<VoyageGeo_VelocityBackground> 
			MakeBackground
			(
				const std::vector<Pnt2d>& theCoords, 
				const std::vector<Vec2d>& theVecolity, 
				const Standard_Real theTol
			);

		static TnbVoyage_EXPORT std::vector<Pnt2d>
			ShortestStraightPath
			(
				const Pnt2d& theStart,
				const Pnt2d& theEnd, 
				const std::shared_ptr<Cad_GeomSurface>& theSurface
			);

		static TnbVoyage_EXPORT std::shared_ptr<Entity2d_Box>
			CalcBoundingBox
			(
				const std::vector<std::shared_ptr<Entity2d_Polygon>>&,
				const Standard_Real theTol
			);

		static TnbVoyage_EXPORT std::vector<std::shared_ptr<Entity2d_Polygon>>
			RetrievePolygons
			(
				const VoyageGeo_Path2& thePath
			);

		static TnbVoyage_EXPORT Standard_Real
			CalcLength
			(
				const Entity2d_Polygon& thePolygon, 
				const Geo2d_MetricPrcsrAnIso&
			);

		// the coordinates points are in longitude and latitude system
		// the result is in meters
		static TnbVoyage_EXPORT Standard_Real CalcDistance(const Pnt2d& theP0, const Pnt2d& theP1);

		static TnbVoyage_EXPORT std::vector<Standard_Real>
			CalcParameters
			(
				const Entity2d_Polygon&, 
				const Geo2d_MetricPrcsrAnIso&, 
				Standard_Real& theTotLength
			);

		static TnbVoyage_EXPORT std::shared_ptr<VoyageMesh_MetricPrcsr>
			MakeMetricPrcsr
			(
				const std::shared_ptr<Geo2d_SizeFunction>& theFun,
				const VoyageGeo_Earth&,
				const Voyage_MetricInfo& theInfo
			);

		static TnbVoyage_EXPORT std::shared_ptr<Geo2d_SizeFunction>
			MakeUniformSizeMap
			(
				const VoyageGeo_Earth&,
				const Standard_Real theSize = 1.0
			);

		// Convert the standard voyage coordinates to the parametric coordinates [8/27/2023 aamir]
		static TnbVoyage_EXPORT Pnt2d ConvertToUV(const Pnt2d&);
		static TnbVoyage_EXPORT Pnt2d ConvertToVoyageSystem(const Pnt2d&);
		static TnbVoyage_EXPORT std::vector<Pnt2d>
			ConvertToVoyageSystem
			(
				const std::vector<Pnt2d>&
			);

		static TnbVoyage_EXPORT std::shared_ptr<Entity2d_Triangulation> 
			ConvertToVoyageSystem
			(
				const Entity2d_Triangulation&
			);

		static TnbVoyage_EXPORT Pnt2d ConvertVoyageToGlobal(const Pnt2d&);

		static TnbVoyage_EXPORT Standard_Real KtsToKmh(const Standard_Real);

		// The route angle is greater than zero if the route turns to the left and is less than zero if turns to the right [8/5/2023 Payvand]
		static Standard_Real CalcRouteAngle(const Pnt2d& theP0, const Pnt2d& theP1, const Pnt2d& theP2);
		
		static TnbVoyage_EXPORT Standard_Real 
			CalcTurningAngle
			(
				const Pnt2d& theP0, 
				const Pnt2d& theP1, 
				const Pnt2d& theP2
			);

		static Vec2d CalcRightsideNormal(const Pnt2d& theP0, const Pnt2d& theP1);
		static Vec2d CalcLeftsideNormal(const Pnt2d& theP0, const Pnt2d& theP1);

		static TnbVoyage_EXPORT std::shared_ptr<Entity2d_Triangulation> 
			RetrieveTriangulation2d
			(
				const std::vector<std::shared_ptr<VoyageMesh_Element>>&
			);

		static TnbVoyage_EXPORT std::shared_ptr<Entity3d_Triangulation>
			RetrieveTriangulation3d
			(
				const std::vector<std::shared_ptr<VoyageMesh_Element>>&
			);

		// Calculate the tangent between two segments (P0P1 & P1P2) that have an intersection on the point p1.
		static TnbVoyage_EXPORT Dir2d
			CalcTangent
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Pnt2d& theP2
			);

		static TnbVoyage_EXPORT void CalcCoord3d
		(
			const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes, 
			const Cad_GeomSurface&
		);

		static TnbVoyage_EXPORT void CalcCoord3d
		(
			const std::vector<std::shared_ptr<VoyageMesh_Node>>& theNodes, 
			const VoyageGeo_Earth&
		);

		static TnbVoyage_EXPORT void SetSourcesToMesh
		(
			const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt2d, Standard_Real>>>& theSources,
			const Standard_Real theBase, 
			const Standard_Real theGrowthRate, 
			GeoMesh2d_SingleBackground& theMesh
		);

		static TnbVoyage_EXPORT void SetInverseSourcesToMesh
		(
			const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt2d, Standard_Real>>>& theSources,
			const Standard_Real theBase,
			const Standard_Real theGrowthRate,
			GeoMesh2d_SingleBackground& theMesh
		);

		static TnbVoyage_EXPORT void ConvertToVoyageSystem(const std::shared_ptr<VoyageWP_Net>&);

	};
}

#endif // !_Voyage_Tools_Header
