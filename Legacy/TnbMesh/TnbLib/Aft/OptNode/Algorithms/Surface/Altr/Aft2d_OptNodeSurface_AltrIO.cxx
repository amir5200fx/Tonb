#include <Aft2d_OptNodeSurface_Altr.hxx>

#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft2d_AltrOptNodeSurface.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_OptNodeSurface_Altr::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<base>(*this);
		ar& theInfo_;
		ar& theAlterAlg_;
	}

	template<>
	template<>
	void Aft2d_OptNodeSurface_Altr::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& boost::serialization::base_object<base>(*this);
		ar& theInfo_;
		ar& theAlterAlg_;
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_OptNodeSurface_Altr);