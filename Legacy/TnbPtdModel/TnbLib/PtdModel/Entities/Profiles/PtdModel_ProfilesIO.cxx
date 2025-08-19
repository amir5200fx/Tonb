#include <PtdModel_Profiles.hxx>

#include <PtdModel_Profile.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_Profiles)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);
	ar & theProfiles_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_Profiles)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);
	ar & theProfiles_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_Profiles);