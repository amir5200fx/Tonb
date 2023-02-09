#pragma once
#ifndef _Mesh_ReferenceValues_Header
#define _Mesh_ReferenceValues_Header

#include <Mesh_SurfaceSizeValues.hxx>
#include <Mesh_SurfaceCurvatureValues.hxx>
#include <Mesh_VariationRate.hxx>
#include <Entity2d_BoxFwd.hxx>

#include <memory>

namespace tnbLib
{

	template<class Box>
	class Mesh_ReferenceValues
	{

		/*Private Data*/

		std::shared_ptr<Box> theRegion_;

		Standard_Real theBase_;

		std::shared_ptr<Mesh_SurfaceSizeValues> theSurfaceSize_;
		std::shared_ptr<Mesh_SurfaceCurvatureValues> theSurfaceCurvature_;

		Mesh_VariationRateInfo theDefaultGrowthRate_;
		Mesh_VariationRateInfo theBoundaryGrowthRate_;


		//- private functions and operators

		void AllocateMemory();

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << " This function is not supposed to be called!" << endl;
			NotImplemented;
		}

	public:

		static TnbMesh_EXPORT const std::string extension;


		//- default constructor

		Mesh_ReferenceValues()
			: theBase_(0)
		{
			theBoundaryGrowthRate_ = Mesh_VariationRateInfo::moderate;
			theDefaultGrowthRate_ = Mesh_VariationRateInfo::moderate;

			AllocateMemory();
		}

		// constructors [12/7/2021 Amir]

		Mesh_ReferenceValues
		(
			const Standard_Real theBaseSize,
			const std::shared_ptr<Box>& theRegion
		)
			: theBase_(theBaseSize)
			, theRegion_(theRegion)
		{
			theBoundaryGrowthRate_ = Mesh_VariationRateInfo::moderate;
			theDefaultGrowthRate_ = Mesh_VariationRateInfo::moderate;

			AllocateMemory();
		}

		Mesh_ReferenceValues
		(
			const Standard_Real theBaseSize,
			std::shared_ptr<Box>&& theRegion
		)
			: theBase_(theBaseSize)
			, theRegion_(std::move(theRegion))
		{
			theBoundaryGrowthRate_ = Mesh_VariationRateInfo::moderate;
			theDefaultGrowthRate_ = Mesh_VariationRateInfo::moderate;

			AllocateMemory();
		}


		//- public functions and operators

		auto BaseSize() const
		{
			return theBase_;
		}

		const auto& Region() const
		{
			return theRegion_;
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

		void SetRegion(const std::shared_ptr<Box>& theRegion)
		{
			theRegion_ = theRegion;
		}

		void SetRegion(std::shared_ptr<Box>&& theRegion)
		{
			theRegion_ = std::move(theRegion);
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

#include <Mesh_ReferenceValuesI.hxx>

#include <Mesh2d_ReferenceValues.hxx>
#include <Mesh3d_ReferenceValues.hxx>

#endif // !_Mesh_ReferenceValues_Header
