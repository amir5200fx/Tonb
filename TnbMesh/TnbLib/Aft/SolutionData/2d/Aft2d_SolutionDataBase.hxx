#pragma once
#ifndef _Aft2d_SolutionDataBase_Header
#define _Aft2d_SolutionDataBase_Header

#include <Global_Serialization.hxx>
#include <Mesh_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_QuadMeshFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>

#include <memory>
#include <map>
#include <set>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;
	class Mesh_Curve_Info;
	class Mesh_BndLayer_Info;

	class Aft2d_SolutionDataBase
	{

		/*Private Data*/


	protected:

		// the geometry [12/4/2021 Amir]
		std::shared_ptr<Cad2d_Plane> thePlane_;


		// curves info [12/4/2021 Amir]
		std::shared_ptr<Mesh_Curve_Info> theGlobalCurveInfo_;
		std::shared_ptr<Mesh_BndLayer_Info> theGlobalBndLayerInfo_;
		
		std::map
			<
			Standard_Integer,
			std::shared_ptr<Mesh_Curve_Info>
			> theCurveInfo_;

		std::map<Standard_Integer, std::shared_ptr<Mesh_BndLayer_Info>>
			theBndLayerInfo_;

		std::set<Standard_Integer> theBndLayerList_;

		// size function map [12/4/2021 Amir]
		std::shared_ptr<Geo2d_SizeFunction> theSizeFun_;

		//- Results

		std::shared_ptr<Entity2d_Polygon> theBoundaryMesh_;
		std::shared_ptr<Entity2d_Triangulation> theMesh_;
		std::vector<std::shared_ptr<Entity2d_QuadMesh>> theBndLayers_;


		// Private functions and operators [12/1/2021 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [12/1/2021 Amir]

		Aft2d_SolutionDataBase()
		{}


		// constructors [12/1/2021 Amir]

	public:

		static TnbMesh_EXPORT const std::string extension;



		// Public functions and operators [12/1/2021 Amir]

		virtual Standard_Boolean IsAnIso() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsIso() const
		{
			return Standard_False;
		}

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& BoundaryMesh() const
		{
			return theBoundaryMesh_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		const auto& BndLayerMeshes() const { return theBndLayers_; }

		const auto& GlobalCurveInfo() const
		{
			return theGlobalCurveInfo_;
		}

		const auto& GlobalBndLayerInfo() const { return theGlobalBndLayerInfo_; }

		const auto& CurveInfo() const
		{
			return theCurveInfo_;
		}

		const auto& BndLayerInfo() const { return theBndLayerInfo_; }
		auto& BndLayerInfoRef() { return theBndLayerInfo_; }

		const auto& BndLayerList() const { return theBndLayerList_; }
		auto& BndLayerListRef() { return theBndLayerList_; }

		auto& CurveInfoRef()
		{
			return theCurveInfo_;
		}

		const auto& SizeFunction() const
		{
			return theSizeFun_;
		}

		void SetBoundaryMesh(const std::shared_ptr<Entity2d_Polygon>& thePoly)
		{
			theBoundaryMesh_ = thePoly;
		}

		void SetBoundaryMesh(std::shared_ptr<Entity2d_Polygon>&& thePoly)
		{
			theBoundaryMesh_ = std::move(thePoly);
		}

		void SetMesh(const std::shared_ptr<Entity2d_Triangulation>& theMesh)
		{
			theMesh_ = theMesh;
		}

		void SetMesh(std::shared_ptr<Entity2d_Triangulation>&& theMesh)
		{
			theMesh_ = std::move(theMesh);
		}

		void SetBndlayerMeshes(const std::vector<std::shared_ptr<Entity2d_QuadMesh>>& theMeshes) 
		{ theBndLayers_ = theMeshes; }

		void SetBndlayerMeshes(std::vector<std::shared_ptr<Entity2d_QuadMesh>>&& theMeshes)
		{
			theBndLayers_ = std::move(theMeshes);
		}

		void LoadPlane(const std::shared_ptr<Cad2d_Plane>& thePlane)
		{
			thePlane_ = thePlane;
		}

		void LoadPlane(std::shared_ptr<Cad2d_Plane>&& thePlane)
		{
			thePlane_ = std::move(thePlane);
		}

		void LoadGlobalCurveInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo)
		{
			theGlobalCurveInfo_ = theInfo;
		}

		void LoadGlobalCurveInfo(std::shared_ptr<Mesh_Curve_Info>&& theInfo)
		{
			theGlobalCurveInfo_ = std::move(theInfo);
		}

		void LoadGlobalBndLayerInfo(const std::shared_ptr<Mesh_BndLayer_Info>& theInfo) 
		{ theGlobalBndLayerInfo_ = theInfo; }

		void LoadCurveInfo(std::map<int, std::shared_ptr<Mesh_Curve_Info>>&& theInfo)
		{
			theCurveInfo_ = std::move(theInfo);
		}

		void LoadSizeFunction(const std::shared_ptr<Geo2d_SizeFunction>& theFun)
		{
			theSizeFun_ = theFun;
		}

		void LoadSizeFunction(std::shared_ptr<Geo2d_SizeFunction>&& theFun)
		{
			theSizeFun_ = std::move(theFun);
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Aft2d_SolutionDataBase);

#endif // !_Aft2d_SolutionData_Header
