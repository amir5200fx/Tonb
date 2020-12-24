#include <ShapePx_Surface.hxx>

#include <SectPx_CurveQ.hxx>
#include <ShapePx_Spacing.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_Surface)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theCurve_;
	ar & theSpace_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_Surface)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theCurve_;
	ar & theSpace_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::ShapePx_Surface);