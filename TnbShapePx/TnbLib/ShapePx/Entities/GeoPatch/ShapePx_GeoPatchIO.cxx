#include <ShapePx_GeoPatch.hxx>

#include <OpenCascade_Serialization.hxx>
#include <Geom_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_GeoPatch)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theGeometry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_GeoPatch)
{
	ar & boost::serialization::base_object<ShapePx_Entity>(*this);
	ar & theGeometry_;
}