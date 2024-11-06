#pragma once
#ifndef _Aft3d_SolutionData_Header
#define _Aft3d_SolutionData_Header
#include <Mesh_Module.hxx>
#include <Entity3d_TetrahedralizationFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Global_Serialization.hxx>

#include <memory>
namespace tnbLib
{
	namespace legLib
	{
		// Forward Declarations
		class Aft3d_SizeFun;

		class Aft3d_SolutionData
		{
			/*Private Data*/
			std::shared_ptr<Entity3d_Triangulation> theSurface_;
			std::shared_ptr<Aft3d_SizeFun> theSizeFun_;
			// results
			std::shared_ptr<Entity3d_Tetrahedralization> theMesh_;

			// Private functions and operators
			TNB_SERIALIZATION(TnbLegMesh_EXPORT);
		public:
			static TnbLegMesh_EXPORT const std::string extension;
			// default constructor
			Aft3d_SolutionData() = default;
			// Public functions and operators
			const auto& Surface() const { return theSurface_; }
			const auto& SizeFun() const { return theSizeFun_; }
			const auto& Mesh() const { return theMesh_; }

			TnbLegMesh_EXPORT void SetSurface(std::shared_ptr<Entity3d_Triangulation> theSurface);
			TnbLegMesh_EXPORT void SetSizeFun(std::shared_ptr<Aft3d_SizeFun> theSizeFun);
			TnbLegMesh_EXPORT void SetMesh(std::shared_ptr<Entity3d_Tetrahedralization> theMesh);
		};
	}
}
#endif