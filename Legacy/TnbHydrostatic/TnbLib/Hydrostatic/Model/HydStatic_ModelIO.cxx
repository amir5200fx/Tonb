#include <HydStatic_Model.hxx>

#include <StbGMaker_Model.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Water.hxx>
#include <Marine_FlatWave.hxx>
#include <HydStatic_FloatBody.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_Model)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theStbModel_;
	Marine_Wave::Save(ar, theWave_);

	ar & theWater_;
	ar & theFloatBody_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_Model)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theStbModel_;
	Marine_Wave::Load(ar, theWave_);

	ar & theWater_;
	ar & theFloatBody_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_Model);

