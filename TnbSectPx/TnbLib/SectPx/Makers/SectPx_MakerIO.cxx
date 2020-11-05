#include <SectPx_Maker.hxx>

#include <SectPx_Registry.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_Maker)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theRegistry_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_Maker)
{
	ar & boost::serialization::base_object<SectPx_Entity>(*this);
	ar & theRegistry_;
}