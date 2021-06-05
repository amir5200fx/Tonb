#include <PtdModel_BladeProfiles.hxx>

#include <PtdModel_BladeProfile.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_BladeProfiles)
{
	ar & boost::serialization::base_object<PtdModel_PropEntity>(*this);
	ar & theProfiles_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_BladeProfiles)
{
	ar & boost::serialization::base_object<PtdModel_PropEntity>(*this);
	ar & theProfiles_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_BladeProfiles);