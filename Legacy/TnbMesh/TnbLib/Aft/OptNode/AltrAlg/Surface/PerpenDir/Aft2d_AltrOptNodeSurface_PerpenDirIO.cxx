#include <Aft2d_AltrOptNodeSurface_PerpenDir.hxx>

#include <Aft_SizeCorr_IterativeInfo.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface_PerpenDir)
{
	ar& boost::serialization::base_object<Aft2d_AltrOptNodeSurface>(*this);

	ar& theInfo_;
	ar& theMaxLev_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface_PerpenDir)
{
	ar& boost::serialization::base_object<Aft2d_AltrOptNodeSurface>(*this);

	ar& theInfo_;
	ar& theMaxLev_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_AltrOptNodeSurface_PerpenDir);