#include <HydStatic_Bonjean.hxx>

#include <Marine_Body.hxx>
#include <Marine_Domain.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Graph.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <HydStatic_BnjCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_Bonjean_Entity)
{
	ar & Section;
	ar & Curve;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_Bonjean_Entity)
{
	ar & Section;
	ar & Curve;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_Bonjean)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	Marine_Body::Save(ar, theBody_);
	ar & theWaters_;

	ar & theBonjean_;
	ar & theGraph_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_Bonjean)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	Marine_Body::Load(ar, theBody_);
	ar & theWaters_;

	ar & theBonjean_;
	ar & theGraph_;
}