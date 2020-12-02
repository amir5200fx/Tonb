#include <SectPx_CmptProfileMaker.hxx>

#include <SectPx_ProfileMaker.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::maker::CmptProfile)
{
	ar & boost::serialization::base_object<SectPx_Maker<SectPx_FrameRegistry>>(*this);
	ar & theProfiles_;
	ar & theCounter_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::maker::CmptProfile)
{
	ar & boost::serialization::base_object<SectPx_Maker<SectPx_FrameRegistry>>(*this);
	ar & theProfiles_;
	ar & theCounter_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::maker::CmptProfile);