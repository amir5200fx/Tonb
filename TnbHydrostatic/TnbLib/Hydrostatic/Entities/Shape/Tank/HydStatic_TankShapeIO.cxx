#include <HydStatic_TankShape.hxx>

#include <Marine_Model_Tank.hxx>
#include <HydStatic_FillCurveQ.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_TankShape)
{
	ar & boost::serialization::base_object<HydStatic_Shape>(*this);

	ar & theTank_;
	ar & theFill_;
	ar & theCross_;
	ar & thePerc_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_TankShape)
{
	ar & boost::serialization::base_object<HydStatic_Shape>(*this);

	ar & theTank_;
	ar & theFill_;
	ar & theCross_;
	ar & thePerc_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_TankShape);