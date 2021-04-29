#include <Cad_GeomSurface.hxx>

#include <OpenCascade_Serialization.hxx>

#include <Geom_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_GeomSurface)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);
	ar & theSurface_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_GeomSurface)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);
	ar & theSurface_;
}