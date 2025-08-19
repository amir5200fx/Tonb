#include <PtdModel_PropHub.hxx>

#include <PtdModel_PropBlade.hxx>
#include <PtdModel_PropHubPars.hxx>
#include <PtdModel_PropHubSection.hxx>
#include <PtdModel_Face.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_PropHub)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theBlade_;
	ar & theParameters_;

	ar & theSection_;

	ar & theFaces_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_PropHub)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theBlade_;
	ar & theParameters_;

	ar & theSection_;

	ar & theFaces_;
}