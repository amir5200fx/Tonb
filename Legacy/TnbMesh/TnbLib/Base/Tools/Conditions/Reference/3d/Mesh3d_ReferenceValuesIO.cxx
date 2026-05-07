#include <Mesh3d_ReferenceValues.hxx>

#include <Entity3d_Box.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh3d_ReferenceValues::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & theRegion_;

		ar & theBase_;

		ar & theSurfaceSize_;

		ar & theSurfaceCurvature_;

		ar & theDefaultGrowthRate_;
		ar & theBoundaryGrowthRate_;
	}

	template<>
	template<>
	void Mesh3d_ReferenceValues::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & theRegion_;

		ar & theBase_;

		ar & theSurfaceSize_;

		ar & theSurfaceCurvature_;

		ar & theDefaultGrowthRate_;
		ar & theBoundaryGrowthRate_;
	}
}