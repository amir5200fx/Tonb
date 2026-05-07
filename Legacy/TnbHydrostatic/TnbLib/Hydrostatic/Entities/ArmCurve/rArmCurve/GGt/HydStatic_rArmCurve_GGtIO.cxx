#include <HydStatic_rArmCurve_GGt.hxx>

#include <HydStatic_rArmCurve_Cmpt.hxx>
#include <HydStatic_rArmCurve_LDV.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_GGt)
{
	ar & boost::serialization::base_object<HydStatic_rArmCurve>(*this);
	ar & theCmpt_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_GGt)
{
	ar & boost::serialization::base_object<HydStatic_rArmCurve>(*this);
	ar & theCmpt_;
}