#include <SectPx_Registry.hxx>

#include <SectPx_RegObj.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_Registry)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theObjects_;
	ar & theCounter_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_Registry)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theObjects_;
	ar & theCounter_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_Registry);