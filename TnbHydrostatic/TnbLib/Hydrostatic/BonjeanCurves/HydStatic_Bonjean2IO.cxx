#include <HydStatic_Bonjean2.hxx>

#include <Marine_CmpSection.hxx>
#include <HydStatic_HydOffsetCurve.hxx>

#include <Marine_Domain.hxx>
#include <Marine_Body.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_Bonjean2::bonjeanEntity)
{
	ar & Section;
	ar & Curve;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_Bonjean2::bonjeanEntity)
{
	ar & Section;
	ar & Curve;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_Bonjean2)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theDomain_;
	ar & theBody_;

	ar & theNbLevels_;
	ar & theLevDistb_;

	ar & theSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_Bonjean2)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theDomain_;
	ar & theBody_;

	ar & theNbLevels_;
	ar & theLevDistb_;

	ar & theSections_;
}