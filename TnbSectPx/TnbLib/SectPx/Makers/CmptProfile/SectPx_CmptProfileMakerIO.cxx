#include <SectPx_CmptProfileMaker.hxx>

#include <SectPx_ProfileMaker.hxx>

DECLARE_SAVE_IMP(tnbLib::maker::CmptProfile)
{
	ar & theProfiles_;
	ar & theCounter_;
}

DECLARE_LOAD_IMP(tnbLib::maker::CmptProfile)
{
	ar & theProfiles_;
	ar & theCounter_;
}