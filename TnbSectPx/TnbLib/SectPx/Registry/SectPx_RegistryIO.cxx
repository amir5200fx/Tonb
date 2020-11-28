#include <SectPx_Registry.hxx>

#include <SectPx_RegObj.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Registry)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & boost::serialization::base_object<SectPx_ScatterRegistry>(*this);
	ar & theObjects_;
	ar & theCounter_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Registry)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & boost::serialization::base_object<SectPx_ScatterRegistry>(*this);
	ar & theObjects_;
	ar & theCounter_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_Registry);