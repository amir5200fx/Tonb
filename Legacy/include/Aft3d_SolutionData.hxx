#pragma once
#ifndef _Aft3d_SolutionData_Header
#define _Aft3d_SolutionData_Header
#include <Mesh_Module.hxx>
#include <Geo3d_SizeFunctionFwd.hxx>
#include <Entity3d_TetrahedralizationFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>

#include <memory>
#include <map>
namespace tnbLib
{
	// Forward Declarations
	class Aft3d_SolutionData_SurfVol;
	class Mesh_Curve_Info;
	class Cad_Volume;

	class Aft3d_SolutionData
	{
	public:
		typedef Cad_Volume volume;
		typedef Geo3d_SizeFunction sizeFun;
		typedef Entity3d_Triangulation surfMesh;
	private:
		/*Private Data*/
		std::shared_ptr<Aft3d_SolutionData_SurfVol> theBndSolu_;

		// results
		std::shared_ptr<Entity3d_Tetrahedralization> theMesh_;

		// Private functions and operators
		TNB_SERIALIZATION(TnbMesh_EXPORT);
	public:
		static TnbMesh_EXPORT const std::string extension;
		// default constructor
		Aft3d_SolutionData() = default;
		// constructors
		TnbMesh_EXPORT Aft3d_SolutionData(std::shared_ptr<Aft3d_SolutionData_SurfVol>& theSolu);

		// Public functions and operators
		const auto& BndSolu() const { return theBndSolu_; }
		const auto& Mesh() const { return theMesh_; }

		TnbMesh_EXPORT void SetBndSolu(std::shared_ptr<Aft3d_SolutionData_SurfVol> theSolu);
		TnbMesh_EXPORT void SetMesh(std::shared_ptr<Entity3d_Tetrahedralization> theMesh);

		// lib
		static TnbMesh_EXPORT std::shared_ptr<volume> RetrieveVolume(const Aft3d_SolutionData&);
		static TnbMesh_EXPORT std::shared_ptr<sizeFun> RetrieveSizeFun(const Aft3d_SolutionData&);
		static TnbMesh_EXPORT std::shared_ptr<surfMesh> RetrieveSurfMesh(const Aft3d_SolutionData&);
	};
}

#endif