#include <SectPx_Overrider.hxx>

#include <SectPx_MasterPnt.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_Overrider)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & thePnt_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_Overrider)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & thePnt_;
}