#include <Geo_MetricPrcsrAnIso_Info.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Geo_MetricPrcsrAnIso_Info)
{
	ar & theNbSamples_;
	ar & theIntgInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Geo_MetricPrcsrAnIso_Info)
{
	ar & theNbSamples_;
	ar & theIntgInfo_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Geo_MetricPrcsrAnIso_Info);