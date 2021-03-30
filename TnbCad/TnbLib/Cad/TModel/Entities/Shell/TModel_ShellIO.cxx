#include <TModel_Shell.hxx>

#include <TModel_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Shell)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theSurfaces_;
	ar & theWaterTight_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Shell)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theSurfaces_;
	ar & theWaterTight_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_Shell);