#include <HydStatic_rArmCurve_Tanks.hxx>

#include <HydStatic_rArmCurve_Cmpt.hxx>
#include <HydStatic_rArmCurve_FSLq.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_Tanks)
{
	ar & boost::serialization::base_object<HydStatic_rArmCurve>(*this);
	ar & theCmpt_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_Tanks)
{
	ar & boost::serialization::base_object<HydStatic_rArmCurve>(*this);
	ar & theCmpt_;
}