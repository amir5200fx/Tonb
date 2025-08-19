#include <SectPx_CmptProfile.hxx>

#include <SectPx_TopoProfile.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_CmptProfile)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theProfiles_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_CmptProfile)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & theProfiles_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_CmptProfile);