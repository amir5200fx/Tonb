#include <ShapePx_Spacing.hxx>

#include <SectPx_Limits.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_Spacing)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theLimits_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_Spacing)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theLimits_;
}