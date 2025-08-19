#include <HydStatic_hArmCurve.hxx>

#include <HydStatic_hAuCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_hArmCurve)
{
	ar & boost::serialization::base_object<HydStatic_ArmCurve>(*this);
	ar & theAuCurve_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_hArmCurve)
{
	ar & boost::serialization::base_object<HydStatic_ArmCurve>(*this);
	ar & theAuCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::hydStcLib::CurveMaker_SymmHeel<tnbLib::HydStatic_hArmCurve>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::hydStcLib::CurveMaker_AsymmHeel<tnbLib::HydStatic_hArmCurve>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::hydStcLib::CurveMaker_StbHeel<tnbLib::HydStatic_hArmCurve>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::hydStcLib::CurveMaker_ArbtHeel<tnbLib::HydStatic_hArmCurve>);