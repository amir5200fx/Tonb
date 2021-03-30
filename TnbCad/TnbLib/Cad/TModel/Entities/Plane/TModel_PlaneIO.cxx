#include <TModel_Plane.hxx>

#include <TModel_ParaWire.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Plane)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theOuter_;
	ar & theInner_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Plane)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theOuter_;
	ar & theInner_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_Plane);