#include <HydStatic_HydOffsetCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_HydOffsetCurve)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & theQs_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_HydOffsetCurve)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & theQs_;
}