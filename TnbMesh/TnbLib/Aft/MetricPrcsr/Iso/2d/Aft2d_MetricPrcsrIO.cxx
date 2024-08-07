#include <Aft2d_MetricPrcsr.hxx>

#include <Geo_MetricPrcsr_Info.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_MetricPrcsr::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			)
	{
		ar & boost::serialization::base_object<base>(*this);

		ar & theInfo_;
	}

	template<>
	template<>
	void Aft2d_MetricPrcsr::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			)
	{
		ar & boost::serialization::base_object<base>(*this);

		ar & theInfo_;
	}
}