#include <Aft2d_tPlnWireSurfaceUniMetric.hxx>

#include <Standard_Transient.hxx>
#include <Aft2d_tPlnCurveSurfaceUniMetric.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Aft2d_tPlnWireSurfaceUniMetric::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);

		ar & theCurves_;
	}

	template<>
	template<>
	void Aft2d_tPlnWireSurfaceUniMetric::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);

		ar & theCurves_;
	}
}