#include <ShapePx_Section.hxx>

#include <SectPx_FrameRegistry.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_Section)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theRegistry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_Section)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theRegistry_;
}