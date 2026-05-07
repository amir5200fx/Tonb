#include <HydStatic_rArmCurve_Eff.hxx>

#include <HydStatic_rAuCurve.hxx>
#include <HydStatic_rArmCurves.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_Eff)
{
	ar & boost::serialization::base_object<HydStatic_rArmCurve>(*this);

	ar & theAuCurve_;
	ar & theBody_;
	ar & theTanks_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::hydStcLib::rArmCurve_Eff)
{
	ar & boost::serialization::base_object<HydStatic_rArmCurve>(*this);

	ar & theAuCurve_;
	ar & theBody_;
	ar & theTanks_;
}