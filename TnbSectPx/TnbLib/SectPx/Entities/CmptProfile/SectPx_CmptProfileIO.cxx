#include <SectPx_CmptProfile.hxx>

#include <SectPx_TopoProfile.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_CmptProfile)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theProfiles_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_CmptProfile)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theProfiles_;
}