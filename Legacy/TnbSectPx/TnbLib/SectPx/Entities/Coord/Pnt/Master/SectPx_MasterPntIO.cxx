#include <SectPx_MasterPnt.hxx>

#include <SectPx_Overrider.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_MasterPnt)
{
	ar & boost::serialization::base_object<SectPx_TPnt>(*this);
	ar & theOverrider_;
	ar & applyOverrider_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_MasterPnt)
{
	ar & boost::serialization::base_object<SectPx_TPnt>(*this);
	ar & theOverrider_;
	ar & applyOverrider_;
}