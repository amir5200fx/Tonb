#include <Geo2d_MetricPrcsr.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Geo_MetricPrcsr_Base<void>)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theDimSize_;
	ar & theInfo_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Geo_MetricPrcsr_Base<void>)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theDimSize_;
	ar & theInfo_;
}