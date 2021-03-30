#include <TModel_Curve.hxx>

#include <OpenCascade_Serialization.hxx>
#include <Geom_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Curve)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theGeometry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Curve)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theGeometry_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_Curve);