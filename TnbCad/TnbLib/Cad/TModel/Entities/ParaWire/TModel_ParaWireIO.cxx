#include <TModel_ParaWire.hxx>

#include <TModel_CmpParaCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_ParaWire)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theCurve_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_ParaWire)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_ParaWire);