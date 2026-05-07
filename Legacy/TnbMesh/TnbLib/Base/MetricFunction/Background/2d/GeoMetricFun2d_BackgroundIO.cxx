#include <GeoMetricFun2d_Background.hxx>

namespace tnbLib
{

	template<>
	template<>
	void GeoMetricFun2d_Background::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<GeoMetricFun_nonUniform<typename GeoMesh2d_MetricBackground::Point>>(*this);
		ar & theBackMesh_;
	}

	template<>
	template<>
	void GeoMetricFun2d_Background::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<GeoMetricFun_nonUniform<typename GeoMesh2d_MetricBackground::Point>>(*this);
		ar & theBackMesh_;
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoMetricFun2d_Background);