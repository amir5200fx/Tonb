#include <PtdModel_PropBlade.hxx>

#include <Geo_xDistb.hxx>
#include <PtdModel_PropSection.hxx>
#include <PtdModel_BladeInfo.hxx>
#include <PtdModel_Profiles.hxx>
#include <PtdModel_xPars.hxx>
#include <PtdModel_BladeView.hxx>
#include <PtdModel_Face.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_PropBlade)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theDistb_;
	ar & theSection_;

	ar & theBladeInfo_;
	ar & theProfiles_;

	ar & theParameters_;
	ar & theBladeView_;

	ar & theBack_;
	ar & theFace_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_PropBlade)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theDistb_;
	ar & theSection_;

	ar & theBladeInfo_;
	ar & theProfiles_;

	ar & theParameters_;
	ar & theBladeView_;

	ar & theBack_;
	ar & theFace_;
}