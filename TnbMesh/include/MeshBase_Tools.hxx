#pragma once
#ifndef _MeshBase_Tools_Header
#define _MeshBase_Tools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Mesh_Module.hxx>
#include <Mesh3d_FacetFwd.hxx>
#include <Mesh3d_ElementFwd.hxx>
#include <Mesh3d_EdgeFwd.hxx>
#include <Mesh3d_NodeFwd.hxx>
#include <Mesh2d_ElementFwd.hxx>
#include <Mesh2d_EdgeFwd.hxx>
#include <Mesh2d_NodeFwd.hxx>
#include <GeoMesh2d_SingleBackgroundFwd.hxx>
#include <GeoMesh3d_SingleBackgroundFwd.hxx>
#include <GeoMesh2d_MetricBackgroundFwd.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>
#include <Global_Serialization.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Entity2d_MetricMeshValueFwd.hxx>
#include <Entity2d_MeshValueFwd.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <array>
#include <vector>
#include <map>
#include <memory>

//- Forward Declarations
class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Pln_Curve;
	class GModel_ParaCurve;
	class TModel_ParaCurve;
	class Entity2d_Metric1;

	template<class Point, class Value>
	class Mesh_SetSourcesNode;

	class MeshBase_Tools
	{

	public:

		static TnbMesh_EXPORT std::tuple<Standard_Integer, Standard_Integer> Ids(const Mesh2d_Edge&);
		static TnbMesh_EXPORT std::tuple<Standard_Integer, Standard_Integer, Standard_Integer> Ids(const Mesh2d_Element&); 

		static TnbMesh_EXPORT std::tuple<Standard_Integer, Standard_Integer> Ids(const Mesh3d_Edge&);
		static TnbMesh_EXPORT std::tuple<Standard_Integer, Standard_Integer, Standard_Integer> Ids(const Mesh3d_Facet&);
		static TnbMesh_EXPORT std::tuple<Standard_Integer, Standard_Integer, Standard_Integer, Standard_Integer> Ids(const Mesh3d_Element&);

		static std::tuple<connectivity::triple, connectivity::triple, connectivity::triple, connectivity::triple>
			FaceIds(const Mesh3d_Element&);

		static TnbMesh_EXPORT std::shared_ptr<Entity2d_Box> 
			CalcBoundingBox
			(
				const std::shared_ptr<Mesh2d_Element>&
			);

		static TnbMesh_EXPORT std::shared_ptr<Entity3d_Box> 
			CalcBoundingBox
			(
				const std::shared_ptr<Mesh3d_Element>&
			);

		static TnbMesh_EXPORT Pnt2d 
			CalcAnalyCoord
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1, 
				const Pnt2d& theCentre, 
				const Entity2d_Metric1& m, 
				const Standard_Real h,
				const Standard_Real len
			);

		/*template<class SourceType>
		static void SetSourcesToMesh3d
		(
			const std::vector<std::shared_ptr<SourceType>>& theSources,
			const Standard_Real theBase,
			GeoMesh3d_Background& theMesh
		);*/

		static TnbMesh_EXPORT void SetSourcesToMeshNearestPoint
		(
			const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt2d, Standard_Real>>>& theSources,
			const Standard_Real theBase,
			const Standard_Real theGrowthRate,
			GeoMesh2d_SingleBackground& theMesh
		);

		static TnbMesh_EXPORT void SetSourcesToMeshNearestPoint
		(
			const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt3d, Standard_Real>>>& theSources,
			const Standard_Real theBase,
			const Standard_Real theGrowthRate,
			GeoMesh3d_SingleBackground& theMesh
		);

		static TnbMesh_EXPORT void SetSourcesToMesh
		(
			const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt3d, Standard_Real>>>& theSources,
			const Standard_Real theBase,
			const Standard_Real theGrowthRate,
			GeoMesh3d_SingleBackground& theMesh	
		);

		static TnbMesh_EXPORT void SetSourcesToMesh
		(
			const std::vector<std::pair<Pnt2d, Standard_Real>>& theSources,
			const Standard_Real theBaseSize,
			GeoMesh2d_SingleBackground& theMesh
		);

		static TnbMesh_EXPORT void SetSourcesToMesh
		(
			const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt2d, Standard_Real>>>& theSources,
			const Standard_Real theBase,
			const Standard_Real theGrowthRate,
			GeoMesh2d_SingleBackground& theMesh
		);

		static TnbMesh_EXPORT std::vector<Standard_Real>
			CalcDeterminants
			(
				const std::vector<Pnt2d>& thePts,
				const Entity2d_MetricMeshValue&
			);

		static TnbMesh_EXPORT std::shared_ptr<Entity2d_MeshValue> 
			CalcDeterminants
			(
				const std::shared_ptr<Entity2d_Triangulation>& theAprx, 
				const Entity2d_MetricMeshValue&
			);

		static TnbMesh_EXPORT Pnt2d 
			CorrectCoord
			(
				const Pnt2d& theCentre, 
				const Pnt2d& theCoord, 
				const Entity2d_Box&
			);

		static TnbMesh_EXPORT std::shared_ptr<Mesh3d_Edge> FindEdge(const Mesh3d_Node&, const Mesh3d_Node&);

		static TnbMesh_EXPORT const Handle(Geom2d_Curve)& Geometry(const std::shared_ptr<Pln_Curve>& theCurve);
		static TnbMesh_EXPORT const Handle(Geom2d_Curve)& Geometry(const std::shared_ptr<TModel_ParaCurve>& theCurve);
		static TnbMesh_EXPORT const Handle(Geom2d_Curve)& Geometry(const std::shared_ptr<GModel_ParaCurve>& theCurve);

		static TnbMesh_EXPORT Standard_Real FirstParameter(const std::shared_ptr<Pln_Curve>& theCurve);
		static TnbMesh_EXPORT Standard_Real FirstParameter(const std::shared_ptr<TModel_ParaCurve>& theCurve);
		static TnbMesh_EXPORT Standard_Real FirstParameter(const std::shared_ptr<GModel_ParaCurve>& theCurve);

		static TnbMesh_EXPORT Standard_Real LastParameter(const std::shared_ptr<Pln_Curve>& theCurve);
		static TnbMesh_EXPORT Standard_Real LastParameter(const std::shared_ptr<TModel_ParaCurve>& theCurve);
		static TnbMesh_EXPORT Standard_Real LastParameter(const std::shared_ptr<GModel_ParaCurve>& theCurve);

		static TnbMesh_EXPORT Standard_Boolean IsSense(const std::shared_ptr<Mesh2d_Element>&, const std::shared_ptr<Mesh2d_Edge>&);
		static TnbMesh_EXPORT Standard_Integer NodePos(const std::shared_ptr<Mesh2d_Element>&, const std::shared_ptr<Mesh2d_Node>&);

		static TnbMesh_EXPORT Standard_Boolean IsSense(const std::shared_ptr<Mesh3d_Facet>&, const std::tuple<connectivity::triple, connectivity::triple, connectivity::triple, connectivity::triple>& theElementFaces);
		static TnbMesh_EXPORT Standard_Boolean IsSense(const std::shared_ptr<Mesh3d_Facet>&, const std::shared_ptr<Mesh3d_Facet>&);
		static TnbMesh_EXPORT Standard_Boolean IsSense(const std::shared_ptr<Mesh3d_Element>&, const std::shared_ptr<Mesh3d_Facet>&);

		static TnbMesh_EXPORT Standard_Boolean IsCoincident(const Standard_Integer i0, const Standard_Integer i1, const Standard_Integer i2, const Mesh3d_Facet&);
		static TnbMesh_EXPORT std::shared_ptr<Mesh3d_Facet> IsOnElement(const Standard_Integer i0, const Standard_Integer i1, const Standard_Integer i2, const Mesh3d_Element&);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh2d_Node>> MakeNodes(const std::vector<Pnt2d>&);

		// Warning! - no edge has been created by calling this function [1/1/2022 Amir]
		//          - no connection is made between elements and nodes
		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh2d_Element>> MakeElements(const Entity2d_Triangulation&);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh3d_Facet>> RetrieveFacets(const std::vector<std::shared_ptr<Mesh3d_Element>>&);
		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh3d_Edge>> RetrieveEdges(const std::vector<std::shared_ptr<Mesh3d_Element>>&);
		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh2d_Edge>> RetrieveEdges(const std::vector<std::shared_ptr<Mesh2d_Element>>&);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh2d_Node>> RetrieveNodes(const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements);
		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh3d_Node>> RetrieveNodes(const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements);
		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh2d_Node>> RetrieveAdjacentNodes(const std::shared_ptr<Mesh2d_Node>&);
		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh3d_Node>> RetrieveAdjacentNodes(const std::shared_ptr<Mesh3d_Node>&);

		// creating edges for the elements [1/1/2022 Amir]
		// note: nodes and edges are connected with creating edges
		static TnbMesh_EXPORT void MakeEdges(const std::vector<std::shared_ptr<Mesh2d_Element>>&);

		static TnbMesh_EXPORT void ConnectNodesAndElements(const std::vector<std::shared_ptr<Mesh2d_Element>>&);
		static TnbMesh_EXPORT void ConnectNodesAndEdges(const std::vector<std::shared_ptr<Mesh2d_Element>>&);
		static TnbMesh_EXPORT void ConnectEdgesAndElements(const std::vector<std::shared_ptr<Mesh2d_Element>>&);
		static TnbMesh_EXPORT void ConnectElements(const std::vector<std::shared_ptr<Mesh2d_Element>>&);

		static TnbMesh_EXPORT void ConnectNodesAndEdges(const std::vector<std::shared_ptr<Mesh2d_Edge>>&);

		static TnbMesh_EXPORT void ConnectNodesAndElements(const std::vector<std::shared_ptr<Mesh3d_Element>>&);
		static TnbMesh_EXPORT void ConnectNodesAndFacets(const std::vector<std::shared_ptr<Mesh3d_Facet>>&);
		static TnbMesh_EXPORT void ConnectNodesAndFacets(const std::vector<std::shared_ptr<Mesh3d_Element>>&);
		static TnbMesh_EXPORT void ConnectNodesAndEdges(const std::vector<std::shared_ptr<Mesh3d_Edge>>&);
		static TnbMesh_EXPORT void ConnectNodesAndEdges(const std::vector<std::shared_ptr<Mesh3d_Element>>&);

		static TnbMesh_EXPORT void ConnectEdgesAndElements(const std::vector<std::shared_ptr<Mesh3d_Element>>&);
		static TnbMesh_EXPORT void ConnectEdgesAndFacets(const std::vector<std::shared_ptr<Mesh3d_Facet>>& theFacets);
		static TnbMesh_EXPORT void ConnectEdgesAndFacets(const std::vector<std::shared_ptr<Mesh3d_Element>>&);

		static TnbMesh_EXPORT void ConnectFacetsAndElements(const std::vector<std::shared_ptr<Mesh3d_Element>>&);

		static TnbMesh_EXPORT void ConnectElements(const std::vector<std::shared_ptr<Mesh3d_Element>>&);

		static TnbMesh_EXPORT void ConnectMesh(const std::vector<std::shared_ptr<Mesh3d_Element>>&);
		static TnbMesh_EXPORT void ConnectMesh(const std::vector<std::shared_ptr<Mesh2d_Element>>&);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh2d_Element>> MakeMesh(const Entity2d_Triangulation&);

		template<class ElementType>
		static std::shared_ptr<ElementType> ElementLocation(const std::shared_ptr<ElementType>& theStart, const typename ElementType::Point& theCoord);

		template<class T>
		static void Save(const std::map<Standard_Integer, std::weak_ptr<T>>& theMap, TNB_oARCH_TYPE& ar)
		{
			std::vector<Standard_Integer> entities;
			for (const auto& e : theMap)
			{
				if (auto x = e.second.lock())
				{
#ifdef _DEBUG
					if (e.first NOT_EQUAL x->Index())
					{
						FatalErrorIn(FunctionSIG)
							<< " unstable data has been detected!" << endl
							<< abort(FatalError);
					}
#endif // _DEBUG
					entities.push_back(x->Index());
				}
				else
				{
					entities.push_back(0);
				}
			}
			ar << entities;
		}

		template<class T>
		static void Save(const std::pair<std::weak_ptr<T>, std::weak_ptr<T>>& thePair, TNB_oARCH_TYPE& ar)
		{
			if (auto x = thePair.first.lock())
			{
				ar << x->Index();
			}
			else
			{
				ar << (Standard_Integer)0;
			}

			if (auto x = thePair.second.lock())
			{
				ar << x->Index();
			}
			else
			{
				ar << (Standard_Integer)0;
			}
		}

		template<class T, std::size_t N>
		static void Save(const std::array<std::weak_ptr<T>, N>& theEntities, TNB_oARCH_TYPE& ar)
		{
			std::vector<Standard_Integer> entities;
			for (const auto& e : theEntities)
			{
				if (auto x = e.lock())
				{
					entities.push_back(x->Index());
				}
				else
				{
					entities.push_back(0);
				}
			}
			ar << entities;
		}

		static inline Standard_Real 
			CalcRadius
			(
				const Standard_Real growthRate, 
				const Standard_Real theTarget,
				const Standard_Real theBase
			);

		static TnbMesh_EXPORT std::shared_ptr<GeoMesh2d_Background> 
			MakeBakground
			(
				const std::vector<Pnt2d>& theCoords,
				const std::vector<Standard_Real>& theValues,
				const Standard_Real theTol
			);

		static TnbMesh_EXPORT std::shared_ptr<GeoMesh2d_MetricBackground>
			MakeBackground
			(
				const std::vector<Pnt2d>& theCoords,
				const std::vector<Entity2d_Metric1>& theValues,
				const Standard_Real theTol
			);
	};
}

#include <MeshBase_ToolsI.hxx>

#endif // !_MeshBase_Tools_Header
