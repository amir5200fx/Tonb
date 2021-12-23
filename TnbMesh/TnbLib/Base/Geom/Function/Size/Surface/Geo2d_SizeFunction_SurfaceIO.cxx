#include <Geo2d_SizeFunction_Surface.hxx>

#include <OpenCascade_Serialization.hxx>
#include <Geo3d_SizeFunction.hxx>

#include <Geom_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Geo2d_SizeFunction_Surface)
{
	ar & boost::serialization::base_object<Geo2d_SizeFunction>(*this);

	ar & theSurface_;
	ar & theSize3d_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Geo2d_SizeFunction_Surface)
{
	ar & boost::serialization::base_object<Geo2d_SizeFunction>(*this);

	ar & theSurface_;
	ar & theSize3d_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Geo2d_SizeFunction_Surface);