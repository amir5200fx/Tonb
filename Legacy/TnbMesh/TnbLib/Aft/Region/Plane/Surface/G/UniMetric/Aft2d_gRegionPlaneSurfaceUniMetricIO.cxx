#include <Aft2d_gRegionPlaneSurfaceUniMetric.hxx>

#include <Aft2d_gPlnWireSurfaceUniMetric.hxx>
#include <GModel_Plane.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_gRegionPlaneSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);

		ar & thePlane_;

		ar & theOuter_;
		ar & theInner_;
	}

	template<>
	template<>
	void Aft2d_gRegionPlaneSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);

		ar & thePlane_;

		ar & theOuter_;
		ar & theInner_;
	}
}