#include <HydStatic_rArmCurve.hxx>

#include <HydStatic_rAuCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_rArmCurve)
{
	ar & boost::serialization::base_object<HydStatic_ArmCurve>(*this);
	//ar & theAuCurve_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_rArmCurve)
{
	ar & boost::serialization::base_object<HydStatic_ArmCurve>(*this);
	//ar & theAuCurve_;
}