#include <TModel_ParaWire.hxx>

#include <TModel_ParaCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_ParaWire)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);
	ar & theCurves_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_ParaWire)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);
	ar & theCurves_;
}