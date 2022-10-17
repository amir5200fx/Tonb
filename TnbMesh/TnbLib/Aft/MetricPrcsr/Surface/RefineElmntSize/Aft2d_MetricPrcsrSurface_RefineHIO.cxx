#include <Aft2d_MetricPrcsrSurface_RefineH.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_MetricPrcsrSurface_RefineH)
{
	ar & boost::serialization::base_object<Aft2d_MetricPrcsrSurface>(*this);

	ar & theCoeff_;
	ar & theDelta_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_MetricPrcsrSurface_RefineH)
{
	ar & boost::serialization::base_object<Aft2d_MetricPrcsrSurface>(*this);

	ar & theCoeff_;
	ar & theDelta_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_MetricPrcsrSurface_RefineH);