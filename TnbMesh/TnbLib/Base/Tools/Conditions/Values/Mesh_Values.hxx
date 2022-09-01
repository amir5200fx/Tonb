#pragma once
#ifndef _Mesh_Values_Header
#define _Mesh_Values_Header

#include <Mesh_SurfaceCurvatureValues.hxx>
#include <Mesh_SurfaceSizeValues.hxx>
#include <Mesh_VariationRateInfo.hxx>

#include <memory>

namespace tnbLib
{

	class Mesh_Values
	{

		/*Private Data*/

		Mesh_VariationRateInfo theBoundaryGrowthRate_;

		std::shared_ptr<Mesh_SurfaceSizeValues> theSurfaceSize_;
		std::shared_ptr<Mesh_SurfaceCurvatureValues> theCurvature_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theBoundaryGrowthRate_;
			ar & theSurfaceSize_;
			ar & theCurvature_;
		}

	public:

		TnbMesh_EXPORT Mesh_Values();

		auto BoundaryGrowthRate() const
		{
			return theBoundaryGrowthRate_;
		}

		const auto& SurfaceSize() const
		{
			return theSurfaceSize_;
		}

		const auto& SurfaceCurvature() const
		{
			return theCurvature_;
		}

		void SetBoundaryGrowthRate(const Mesh_VariationRateInfo info)
		{
			theBoundaryGrowthRate_ = info;
		}
	};
}

#endif // !_Mesh_Values_Header
