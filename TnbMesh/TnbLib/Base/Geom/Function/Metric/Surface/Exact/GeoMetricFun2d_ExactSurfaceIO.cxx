#include <GeoMetricFun2d_ExactSurface.hxx>

#include <OpenCascade_Serialization.hxx>
#include <Geom_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoMetricFun2d_ExactSurface)
{
	ar & boost::serialization::base_object<GeoMetricFun2d_nonUniform>(*this);
	ar & theSurface_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoMetricFun2d_ExactSurface)
{
	ar & boost::serialization::base_object<GeoMetricFun2d_nonUniform>(*this);
	ar & theSurface_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoMetricFun2d_ExactSurface);