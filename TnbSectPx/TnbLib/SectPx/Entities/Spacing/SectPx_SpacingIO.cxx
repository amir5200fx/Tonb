#include <SectPx_Spacing.hxx>

#include <SectPx_Limits.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Spacing)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);
	ar & theLimits_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Spacing)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);
	ar & theLimits_;
}