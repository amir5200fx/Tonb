#include <GModel_ParaWire.hxx>

#include <GModel_ParaCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_ParaWire)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theCurves_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_ParaWire)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theCurves_;
}