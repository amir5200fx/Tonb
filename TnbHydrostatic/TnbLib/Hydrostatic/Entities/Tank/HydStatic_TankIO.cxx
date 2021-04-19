#include <HydStatic_Tank.hxx>

#include <Marine_Model_Tank.hxx>
#include <HydStatic_FillCurve.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_Tank)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & theTank_;
	ar & theFill_;
	ar & theCross_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_Tank)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & theTank_;
	ar & theFill_;
	ar & theCross_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_Tank);