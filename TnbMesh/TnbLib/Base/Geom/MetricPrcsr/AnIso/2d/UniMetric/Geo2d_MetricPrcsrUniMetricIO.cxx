#include <Geo2d_MetricPrcsrUniMetric.hxx>

#include <Geo_MetricPrcsr_Info.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Geo_MetricPrcsr_Base<tnbLib::GeoMetricFun2d_Uniform>)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theDimSize_;
	ar & theInfo_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Geo_MetricPrcsr_Base<tnbLib::GeoMetricFun2d_Uniform>)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theDimSize_;
	ar & theInfo_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Geo2d_MetricPrcsrUniMetric);