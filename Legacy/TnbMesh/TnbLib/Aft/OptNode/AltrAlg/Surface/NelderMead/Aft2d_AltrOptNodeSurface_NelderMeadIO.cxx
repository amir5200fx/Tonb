#include <Aft2d_AltrOptNodeSurface_NelderMead.hxx>

#include <NumAlg_NelderMeadInfo.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface_NelderMead)
{
	ar& boost::serialization::base_object<Aft2d_AltrOptNodeSurface>(*this);

	ar& theInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface_NelderMead)
{
	ar& boost::serialization::base_object<Aft2d_AltrOptNodeSurface>(*this);

	ar& theInfo_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_AltrOptNodeSurface_NelderMead);