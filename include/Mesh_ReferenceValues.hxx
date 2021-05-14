#pragma once
#ifndef _Mesh_ReferenceValues_Header
#define _Mesh_ReferenceValues_Header

#include <Mesh_SurfaceSizeValues.hxx>
#include <Mesh_SurfaceCurvatureValues.hxx>
#include <Mesh_VariationRate.hxx>

namespace tnbLib
{

	class Mesh_ReferenceValues
	{

		/*Private Data*/


		Standard_Real theBase_;

		Mesh_SurfaceSizeValues theSurfaceSize_;

		Mesh_SurfaceCurvatureValues theSurfaceCurvature_;

		Mesh_VariationRateInfo theDefaultGrowthRate_;
		Mesh_VariationRateInfo theBoundaryGrowthRate_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theBase_;
			ar & theSurfaceSize_;
			ar & theSurfaceCurvature_;
			ar & theDefaultGrowthRate_;
			ar & theBoundaryGrowthRate_;
		}


		Mesh_ReferenceValues()
			: theBase_(0)
		{}

	public:

		TnbMesh_EXPORT Mesh_ReferenceValues(const Standard_Real theBaseSize);


		//- public functions and operators

		auto BaseSize() const
		{
			return theBase_;
		}

		auto& ChangeBaseSize()
		{
			return theBase_;
		}

		const auto& SurfaceSize() const
		{
			return theSurfaceSize_;
		}

		auto& SurfaceSizeRef()
		{
			return theSurfaceSize_;
		}

		const auto& SurfaceCurvature() const
		{
			return theSurfaceCurvature_;
		}

		auto& SurfaceCurvatureRef()
		{
			return theSurfaceCurvature_;
		}

		auto DefaultGrowthRate() const
		{
			return theDefaultGrowthRate_;
		}

		auto BoundaryGrowthRate() const
		{
			return theBoundaryGrowthRate_;
		}

		void SetBaseSize(const Standard_Real theSize)
		{
			theBase_ = theSize;
		}

		void SetDefaultGrowthRate(const Mesh_VariationRateInfo info)
		{
			theDefaultGrowthRate_ = info;
		}

		void SetBoundaryGrowthRate(const Mesh_VariationRateInfo info)
		{
			theBoundaryGrowthRate_ = info;
		}

	};
}

#endif // !_Mesh_ReferenceValues_Header
