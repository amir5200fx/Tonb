#include <HydStatic_rArmCurve_TCG.hxx>

#include <HydStatic_rArmCurve_LDT.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_TCG)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & theLoad_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_TCG)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & theLoad_;
}