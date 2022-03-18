#include <Aft2d_tPatchUniMetric.hxx>

#include <TModel_Surface.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity3d_Triangulation.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_tPatchUniMetric::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);

		ar & theSurface_;
		ar & theParaTriangulation_;
		ar & theSurfaceTriangulation_;
	}

	template<>
	template<>
	void Aft2d_tPatchUniMetric::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);

		ar & theSurface_;
		ar & theParaTriangulation_;
		ar & theSurfaceTriangulation_;
	}
}