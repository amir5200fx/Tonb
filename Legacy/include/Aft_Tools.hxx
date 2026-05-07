#pragma once
#ifndef _Aft_Tools_Header
#define _Aft_Tools_Header

#include <Mesh_Module.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity_Connectivity.hxx>
#include <Aft2d_NodeFwd.hxx>
#include <Aft2d_NodeAnIsoFwd.hxx>
#include <Aft2d_NodeSurfaceFwd.hxx>
#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft2d_SegmentEdgeFwd.hxx>
#include <Aft2d_SegmentEdgeAnIsoFwd.hxx>
#include <Aft2d_gSegmentEdgeFwd.hxx>
#include <Aft2d_tSegmentEdgeFwd.hxx>
#include <Aft2d_SegmentEdgeUniMetricFwd.hxx>
#include <Aft2d_gSegmentEdgeUniMetricFwd.hxx>
#include <Aft2d_tSegmentEdgeUniMetricFwd.hxx>
#include <Aft2d_PlnCurveFwd.hxx>
#include <Aft2d_PlnCurveAnIsoFwd.hxx>
#include <Aft2d_PlnCurveUniMetricFwd.hxx>
#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>
#include <Aft_ElementsFwd.hxx>
#include <Aft_NodesFwd.hxx>
#include <Aft3d_FacetFwd.hxx>
#include <Aft3d_EdgeFwd.hxx>
#include <Geo2d_MetricPrcsrFwd.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Pnt3d;
	class Mesh_Curve_Info;

	class Aft_Tools
	{

	public:

		static TnbMesh_EXPORT const Pnt2d& GetCoord0(const Aft2d_Edge&);
		static TnbMesh_EXPORT const Pnt2d& GetCoord1(const Aft2d_Edge&);

		static TnbMesh_EXPORT const Pnt2d& GetCoord0(const Aft2d_EdgeAnIso&);
		static TnbMesh_EXPORT const Pnt2d& GetCoord1(const Aft2d_EdgeAnIso&);

		static TnbMesh_EXPORT const Pnt2d& GetCoord0(const Aft2d_EdgeSurface&);
		static TnbMesh_EXPORT const Pnt2d& GetCoord1(const Aft2d_EdgeSurface&);

		static TnbMesh_EXPORT const Pnt3d& GetCoord0(const Aft3d_Edge&);
		static TnbMesh_EXPORT const Pnt3d& GetCoord1(const Aft3d_Edge&);

		static TnbMesh_EXPORT std::tuple<Pnt2d, Pnt2d> GetCoords(const Aft2d_Edge&);
		static TnbMesh_EXPORT std::tuple<Pnt2d, Pnt2d> GetCoords(const Aft2d_EdgeAnIso&);
		static TnbMesh_EXPORT std::tuple<Pnt2d, Pnt2d> GetCoords(const Aft2d_EdgeSurface&);
		static TnbMesh_EXPORT std::tuple<Pnt3d, Pnt3d> GetCoords(const Aft3d_Edge&);

		static TnbMesh_EXPORT const Pnt2d& GetCoord0(const Aft2d_Element&);
		static TnbMesh_EXPORT const Pnt2d& GetCoord1(const Aft2d_Element&);
		static TnbMesh_EXPORT const Pnt2d& GetCoord2(const Aft2d_Element&);

		static TnbMesh_EXPORT const Pnt2d& GetCoord0(const Aft2d_ElementAnIso&);
		static TnbMesh_EXPORT const Pnt2d& GetCoord1(const Aft2d_ElementAnIso&);
		static TnbMesh_EXPORT const Pnt2d& GetCoord2(const Aft2d_ElementAnIso&);

		static TnbMesh_EXPORT const Pnt2d& GetCoord0(const Aft2d_ElementSurface&);
		static TnbMesh_EXPORT const Pnt2d& GetCoord1(const Aft2d_ElementSurface&);
		static TnbMesh_EXPORT const Pnt2d& GetCoord2(const Aft2d_ElementSurface&);

		static TnbMesh_EXPORT std::tuple<Pnt2d, Pnt2d, Pnt2d> GetCoords(const Aft2d_Element&);
		static TnbMesh_EXPORT std::tuple<Pnt2d, Pnt2d, Pnt2d> GetCoords(const Aft2d_ElementAnIso&);
		static TnbMesh_EXPORT std::tuple<Pnt2d, Pnt2d, Pnt2d> GetCoords(const Aft2d_ElementSurface&);

		static TnbMesh_EXPORT const Pnt3d& GetCoord0(const Aft3d_Element&);
		static TnbMesh_EXPORT const Pnt3d& GetCoord1(const Aft3d_Element&);
		static TnbMesh_EXPORT const Pnt3d& GetCoord2(const Aft3d_Element&);
		static TnbMesh_EXPORT const Pnt3d& GetCoord3(const Aft3d_Element&);

		static TnbMesh_EXPORT std::tuple<Pnt3d, Pnt3d, Pnt3d, Pnt3d> GetCoords(const Aft3d_Element&);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_Edge>> 
			UpCast
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_EdgeAnIso>> 
			UpCast
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>
			UpCast
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_EdgeSurface>> 
			UpCast
			(
				const std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_EdgeSurface>> 
			UpCast
			(
				const std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_EdgeSurface>>
			UpCast
			(
				const std::vector<std::shared_ptr<Aft2d_gSegmentEdgeUniMetric>>&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_EdgeSurface>>
			UpCast
			(
				const std::vector<std::shared_ptr<Aft2d_tSegmentEdgeUniMetric>>&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_Node>> 
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Aft2d_Edge>>& theEdges
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_NodeAnIso>> 
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Aft2d_EdgeAnIso>>& theEdges
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_NodeSurface>> 
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEdges
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_Node>>
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Aft2d_Element>>& theElements
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_NodeAnIso>>
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Aft2d_ElementAnIso>>& theElements
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_NodeSurface>>
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Aft2d_ElementSurface>>& theElements
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft3d_Node>>
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Aft3d_Element>>& theElements
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft3d_Node>>
			RetrieveNodes
			(
				const std::vector<std::shared_ptr<Aft3d_Facet>>&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_Edge>>
			RetrieveEdges(const std::vector<std::shared_ptr<Aft2d_Element>>&);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft3d_Edge>> 
			RetrieveEdges
			(
				const std::vector<std::shared_ptr<Aft3d_Facet>>&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft3d_Edge>>
			RetrieveEdges
			(
				const std::vector<std::shared_ptr<Aft3d_Element>>& theElements
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft3d_Facet>> 
			RetrieveFacets
			(
				const std::vector<std::shared_ptr<Aft3d_Element>>& theElements
			);

		static TnbMesh_EXPORT std::vector<Pnt2d> 
			RetrieveGeometry
			(
				const std::vector<std::shared_ptr<Aft2d_Node>>& theNodes
			);

		static TnbMesh_EXPORT std::vector<Pnt2d> 
			RetrieveGeometry
			(
				const std::vector<std::shared_ptr<Aft2d_NodeAnIso>>& theNodes
			);

		static TnbMesh_EXPORT std::vector<Pnt2d> 
			RetrieveGeometry
			(
				const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theNodes
			);

		template<class EdgeType>
		static std::vector<connectivity::dual> 
			RetrieveEdgeConnectivities
			(
				const std::vector<std::shared_ptr<EdgeType>>& theEdges
			);

		template<class ElmType>
		static std::vector<connectivity::triple>
			RetrieveTriangleConnectivities
			(
				const std::vector<std::shared_ptr<ElmType>>& theElements
			);

		template<>
		static TnbMesh_EXPORT std::vector<connectivity::triple>
			RetrieveTriangleConnectivities<Aft2d_EdgeSurface>
			(
				const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theElements
			);

		template<class ElmType, class NodeType>
		static std::vector<connectivity::triple>
			RetrieveTriangleConnectivities
			(
				const std::vector<std::shared_ptr<NodeType>>& theNodes,
				const std::vector<std::shared_ptr<ElmType>>& theElements
			);

		template<class ElmType>
		static std::vector<connectivity::triple>
			RetrieveTriangleConnectivities
			(
				const std::vector<std::shared_ptr<ElmType>>& theElements,
				const std::map<Standard_Integer, Standard_Integer>& theIndices
			);

		template<>
		static TnbMesh_EXPORT std::vector<connectivity::triple>
			RetrieveTriangleConnectivities<Aft2d_EdgeSurface>
			(
				const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theElements,
				const std::map<Standard_Integer, Standard_Integer>& theIndices
			);

		template<class EntityType>
		static Standard_Integer 
			MaxIndex
			(
				const std::vector<std::shared_ptr<EntityType>>& theEntities
			);

		static Standard_Integer CalcNbNodes(const std::vector<std::shared_ptr<Aft3d_Facet>>&);
		static TnbMesh_EXPORT Standard_Integer
			CalcNbEdges
			(
				const std::vector<std::shared_ptr<Aft3d_Facet>>&
			);

		template<class EntityType>
		static std::map<Standard_Integer, Standard_Integer> 
			CompactIndices
			(
				const std::vector<std::shared_ptr<EntityType>>& theEntities
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdge>> 
			RetrieveTopoMesh
			(
				const std::shared_ptr<Aft2d_PlnCurve>& theCurve,
				const std::shared_ptr<Geo2d_MetricPrcsr>& thePrcsr,
				const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>> 
			RetrieveTopoMesh
			(
				const std::shared_ptr<Aft2d_PlnCurveAnIso>& theCurve,
				const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& thePrcsr,
				const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>
			RetrieveTopoMesh
			(
				const std::shared_ptr<Aft2d_PlnCurveUniMetric>& theCurve,
				const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& thePrcsr,
				const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>
			RetrieveTopoMesh
			(
				const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve,
				const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& thePrcsr,
				const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdge>> 
			RetrieveTopoMesh
			(
				const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve,
				const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& thePrcsr,
				const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);

		template<class EdgeType>
		static std::shared_ptr<Entity2d_Chain> 
			RetrieveEdgeMesh
			(
				const std::vector<std::shared_ptr<EdgeType>>&
			);

		template<class ElmType>
		static std::shared_ptr<Entity2d_Triangulation>
			RetrieveTriangleMesh(const std::vector<std::shared_ptr<ElmType>>&);

		static TnbMesh_EXPORT void
			MergeDangles
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&,
				const Standard_Real tol
			);

		static TnbMesh_EXPORT void
			MergeDangles
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>&,
				const Standard_Real tol
			);

		static TnbMesh_EXPORT void
			MergeDangles
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>&,
				const Standard_Real tol
			);

		static TnbMesh_EXPORT void
			ActiveBoundaryEdges
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&
			);

		static TnbMesh_EXPORT void 
			ActiveBoundaryEdges
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>&
			);

		static TnbMesh_EXPORT void
			ActiveBoundaryEdges
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>&
			);

		static TnbMesh_EXPORT void 
			CalcCood3d
			(
				const std::vector<std::shared_ptr<Aft2d_NodeSurface>>& theNodes, 
				const Geom_Surface&
			);

		// connect the nodes to the edges [12/19/2021 Amir]
		template<class EdgeType>
		static void Connect(const std::vector<std::shared_ptr<EdgeType>>&);

		template<class EdgeType>
		static Standard_Boolean 
			IsIntersect
			(
				const EdgeType& theEdge0,
				const EdgeType& theEdge1
			);

		//static void ActiveBoundaryEdges(const std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>&);

		//static void ActiveBoundaryEdges(const std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>&);
	};
}

#include <Aft_ToolsI.hxx>

#endif // !_Aft_Tools_Header
