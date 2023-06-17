#include <Cad_MultiVolume.hxx>

#include <Cad_Solid.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_MultiVolume)
{
	ar& boost::serialization::base_object<Cad_Volume>(*this);
	ar& theSolids_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_MultiVolume)
{
	ar& boost::serialization::base_object<Cad_Volume>(*this);
	ar& theSolids_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad_MultiVolume);