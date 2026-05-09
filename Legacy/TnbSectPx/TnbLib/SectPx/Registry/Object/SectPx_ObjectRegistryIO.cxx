#include <SectPx_ObjectRegistry.hxx>

#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_RegObj.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_ObjectRegistry)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theCounter_;
	ar & theScatter_;
	ar & theObjects_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_ObjectRegistry)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theCounter_;
	ar & theScatter_;
	ar & theObjects_;
}