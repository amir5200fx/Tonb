#include <Aft2d_gPlnWireSurface.hxx>

#include <Aft2d_gPlnCurveSurface.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Aft2d_gPlnWireSurface::serialize<TNB_iARCH_TYPE>
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
	void Aft2d_gPlnWireSurface::serialize<TNB_oARCH_TYPE>
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