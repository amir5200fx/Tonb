#include <Mesh2d_SolutionData.hxx>

#include <Cad2d_Plane.hxx>
#include <Mesh_ReferenceValues.hxx>

#include <Mesh2d_BoundarySizeMapControl.hxx>
#include <Mesh2d_FeatureSizeMapControl.hxx>
#include <Mesh2d_VolumetricSizeMapControl.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh2d_SolutionData::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar & theGeometry_;
		ar & theReferences_;

		ar & theBoundaries_;
		ar & theFeatures_;
		ar & theVolumetrics_;
	}

	template<>
	template<>
	void Mesh2d_SolutionData::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar & theGeometry_;
		ar & theReferences_;

		ar & theBoundaries_;
		ar & theFeatures_;
		ar & theVolumetrics_;
	}
}