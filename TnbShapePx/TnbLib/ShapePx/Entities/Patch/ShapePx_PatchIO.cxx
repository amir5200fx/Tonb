#include <ShapePx_Patch.hxx>

#include <ShapePx_Section.hxx>
#include <SectPx_Registry.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_Patch)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theSection_;
	ar & theRegistry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_Patch)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theSection_;
	ar & theRegistry_;
}