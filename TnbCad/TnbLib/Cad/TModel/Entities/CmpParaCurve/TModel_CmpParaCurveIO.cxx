#include <TModel_CmpParaCurve.hxx>

#include <TModel_ParaCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_CmpParaCurve)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theCurves_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_CmpParaCurve)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_CmpParaCurve);