#include <Cad_SingleVolume.hxx>

#include <Cad_Solid.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_SingleVolume)
{
	ar& boost::serialization::base_object<Cad_Volume>(*this);
	ar& theSolid_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_SingleVolume)
{
	ar& boost::serialization::base_object<Cad_Volume>(*this);
	ar& theSolid_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad_SingleVolume);