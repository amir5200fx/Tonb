#include <GModel_MetricAnalyzer.hxx>

#include <Cad_GModel.hxx>
#include <Cad_ApprxMetricInfo.hxx>
#include <Entity2d_Metric1.hxx>
#include <Entity2d_MetricMeshValue.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_MetricAnalyzer)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theModel_;
	ar & theMetrics_;

	ar & theGlobalInfo_;
	ar & theInfos_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_MetricAnalyzer)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theModel_;
	ar & theMetrics_;

	ar & theGlobalInfo_;
	ar & theInfos_;
}