#pragma once
#ifndef _MeshBase_Tools_Header
#define _MeshBase_Tools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Mesh_Module.hxx>
#include <Mesh2d_ElementFwd.hxx>
#include <Mesh2d_EdgeFwd.hxx>
#include <Mesh2d_NodeFwd.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>
#include <Global_Serialization.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
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

	class MeshBase_Tools
	{

	public:

		static TnbMesh_EXPORT void SetSourcesToMesh
		(
			const std::vector<std::pair<Pnt2d, Standard_Real>>& theSources,
			const Standard_Real theBaseSize,
			GeoMesh2d_Background& theMesh
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

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh2d_Node>> MakeNodes(const std::vector<Pnt2d>&);

		// Warning! - no edge has been created by calling this function [1/1/2022 Amir]
		//          - no connection is made between elements and nodes
		static TnbMesh_EXPORT std::vector<std::shared_ptr<Mesh2d_Element>> MakeElements(const Entity2d_Triangulation&);

		// creating edges for the elements [1/1/2022 Amir]
		// note: nodes and edges are connected with creating edges
		static TnbMesh_EXPORT void MakeEdges(const std::vector<std::shared_ptr<Mesh2d_Element>>&);

		static TnbMesh_EXPORT void ConnectNodesAndElements(const std::vector<std::shared_ptr<Mesh2d_Element>>&);
		static TnbMesh_EXPORT void ConnectNodesAndEdges(const std::vector<std::shared_ptr<Mesh2d_Element>>&);
		static TnbMesh_EXPORT void ConnectEdgesAndElements(const std::vector<std::shared_ptr<Mesh2d_Element>>&);
		static TnbMesh_EXPORT void ConnectElements(const std::vector<std::shared_ptr<Mesh2d_Element>>&);

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
	};
}

#include <MeshBase_ToolsI.hxx>

#endif // !_MeshBase_Tools_Header
