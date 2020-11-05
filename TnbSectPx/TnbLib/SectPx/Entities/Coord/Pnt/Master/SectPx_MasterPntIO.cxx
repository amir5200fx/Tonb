#include <SectPx_MasterPnt.hxx>

#include <SectPx_Overrider.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_MasterPnt)
{
	ar & boost::serialization::base_object<SectPx_TPnt>(*this);
	ar & theOverrider_;
	ar & applyOverrider_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_MasterPnt)
{
	ar & boost::serialization::base_object<SectPx_TPnt>(*this);
	ar & theOverrider_;
	ar & applyOverrider_;
}