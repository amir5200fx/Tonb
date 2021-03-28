#include <HydStatic_rArmCurve_GGv.hxx>

#include <HydStatic_rArmCurve_Cmpt.hxx>
#include <HydStatic_rArmCurve_LDT.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_GGv)
{
	ar & boost::serialization::base_object<HydStatic_rArmCurve>(*this);
	ar & theCmpt_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_GGv)
{
	ar & boost::serialization::base_object<HydStatic_rArmCurve>(*this);
	ar & theCmpt_;
}