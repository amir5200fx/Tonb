#include <Aft2d_MetricPrcsrSurfaceUniMetric_RefineH.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH)
{
	boost::serialization::base_object<Aft2d_MetricPrcsrSurfaceUniMetric>(*this);

	ar & theCoeff_;
	ar & theDelta_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH)
{
	boost::serialization::base_object<Aft2d_MetricPrcsrSurfaceUniMetric>(*this);

	ar & theCoeff_;
	ar & theDelta_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_MetricPrcsrSurfaceUniMetric_RefineH);