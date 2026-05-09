#include <Aft2d_OptNodeAnIso_Standard.hxx>

#include <Aft_SizeCorr_IterativeInfo.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_OptNodeAnIso_Standard::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<base>(*this);
		ar& theInfo_;
	}

	template<>
	template<>
	void Aft2d_OptNodeAnIso_Standard::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<base>(*this);
		ar& theInfo_;
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_OptNodeAnIso_Standard);