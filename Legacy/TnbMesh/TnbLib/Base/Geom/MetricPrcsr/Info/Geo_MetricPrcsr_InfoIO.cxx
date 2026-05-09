#include <Geo_MetricPrcsr_Info.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Geo_MetricPrcsr_Info)
{
	ar & theIntgInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Geo_MetricPrcsr_Info)
{
	ar & theIntgInfo_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Geo_MetricPrcsr_Info);