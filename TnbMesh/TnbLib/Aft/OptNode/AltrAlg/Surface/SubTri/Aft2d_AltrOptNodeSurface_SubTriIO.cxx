#include <Aft2d_AltrOptNodeSurface_SubTri.hxx>

#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <NumAlg_NelderMeadInfo.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface_SubTri)
{
	ar& boost::serialization::base_object<Aft2d_AltrOptNodeSurface>(*this);
	ar& theSizeCorrInfo_;
	ar& theNelderInfo_;

	ar& theMaxLev_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface_SubTri)
{
	ar& boost::serialization::base_object<Aft2d_AltrOptNodeSurface>(*this);
	ar& theSizeCorrInfo_;
	ar& theNelderInfo_;

	ar& theMaxLev_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_AltrOptNodeSurface_SubTri);