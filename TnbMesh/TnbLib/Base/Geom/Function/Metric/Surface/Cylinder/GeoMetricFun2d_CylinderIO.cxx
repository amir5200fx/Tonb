#include <GeoMetricFun2d_Cylinder.hxx>

#include <OpenCascade_Serialization.hxx>
#include <opencascade/Geom_CylindricalSurface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoMetricFun2d_Cylinder)
{
	ar& boost::serialization::base_object<GeoMetricFun2d_Uniform>(*this);

	Handle(Geom_Surface) surface = Geometry();
	ar& surface;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoMetricFun2d_Cylinder)
{
	ar& boost::serialization::base_object<GeoMetricFun2d_Uniform>(*this);

	Handle(Geom_Surface) surface;
	ar& surface;
	theSurface_ = Handle(Geom_CylindricalSurface)::DownCast(surface);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoMetricFun2d_Cylinder);