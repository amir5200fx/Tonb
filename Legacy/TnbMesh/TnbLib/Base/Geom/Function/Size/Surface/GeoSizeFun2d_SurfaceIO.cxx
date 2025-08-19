#include <GeoSizeFun2d_Surface.hxx>

#include <OpenCascade_Serialization.hxx>
#include <Geo3d_SizeFunction.hxx>

#include <opencascade/Geom_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoSizeFun2d_Surface)
{
	ar & boost::serialization::base_object<Geo2d_SizeFunction>(*this);

	ar & theSurface_;
	ar & theSize3d_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoSizeFun2d_Surface)
{
	ar & boost::serialization::base_object<Geo2d_SizeFunction>(*this);

	ar & theSurface_;
	ar & theSize3d_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoSizeFun2d_Surface);