#pragma once
#ifndef _Mesh_Conditions_Header
#define _Mesh_Conditions_Header

#include <Mesh_SurfaceCurvatureInfo.hxx>
#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Mesh_Conditions
	{

		/*Private Data*/


		Standard_Boolean CustomBoundaryGrowthRate_;
		Standard_Boolean CustomSurfaceSize_;

		Mesh_SurfaceCurvatureInfo theCustomSurfaceCurvature_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & CustomBoundaryGrowthRate_;
			ar & CustomSurfaceSize_;

			ar & theCustomSurfaceCurvature_;
		}

	public:

		TnbMesh_EXPORT Mesh_Conditions();


		auto CustomBoundaryGrowthRate() const
		{
			return CustomBoundaryGrowthRate_;
		}

		auto CustomSurfaceSize() const
		{
			return CustomSurfaceSize_;
		}

		auto CustomSurfaceCurvature() const
		{
			return theCustomSurfaceCurvature_;
		}

		void SetCustomBoundaryGrowthRate(const Standard_Boolean customBoundaryGrowthRate)
		{
			CustomBoundaryGrowthRate_ = customBoundaryGrowthRate;
		}

		void SetCustomSurfaceSize(const Standard_Boolean customSurfaceSize)
		{
			CustomSurfaceSize_ = customSurfaceSize;
		}

		void SetCustomSurfaceCurvature(const Mesh_SurfaceCurvatureInfo SurfaceCurvatureInfo)
		{
			theCustomSurfaceCurvature_ = SurfaceCurvatureInfo;
		}
	};
}

#endif // !_Mesh_Conditions_Header
