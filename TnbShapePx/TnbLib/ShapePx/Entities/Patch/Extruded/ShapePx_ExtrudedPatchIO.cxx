#include <ShapePx_ExtrudedPatch.hxx>

#include <ShapePx_Profile.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_ExtrudedPatch)
{
	ar & boost::serialization::base_object<ShapePx_Patch>(*this);
	ar & theParToProfile_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_ExtrudedPatch)
{
	ar & boost::serialization::base_object<ShapePx_Patch>(*this);
	ar & theParToProfile_;
}

