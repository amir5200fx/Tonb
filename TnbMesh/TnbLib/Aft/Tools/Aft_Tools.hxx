#pragma once
#ifndef _Aft_Tools_Header
#define _Aft_Tools_Header

#include <Mesh_Module.hxx>
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
#include <Aft2d_PlnCurveFwd.hxx>
#include <Aft2d_PlnCurveAnIsoFwd.hxx>
#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>
#include <Geo2d_MetricPrcsrFwd.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Pnt3d;
	class Mesh_Curve_Info;

	class Aft_Tools
	{

	public:

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
			ActiveBoundaryEdges
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>&
			);

		static TnbMesh_EXPORT void 
			ActiveBoundaryEdges
			(
				const std::vector<std::shared_ptr<Aft2d_SegmentEdgeAnIso>>&
			);

		//static void ActiveBoundaryEdges(const std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>&);

		//static void ActiveBoundaryEdges(const std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>&);
	};
}

#endif // !_Aft_Tools_Header
