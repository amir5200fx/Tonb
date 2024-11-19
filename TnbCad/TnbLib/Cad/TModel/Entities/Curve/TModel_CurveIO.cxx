#include <TModel_Curve.hxx>

#include <OpenCascade_Serialization.hxx>
#include <opencascade/Geom_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Curve)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);

	bool hasGeom = false;
	if (theGeometry_)
	{
		hasGeom = true;
		ar & hasGeom;
		ar & theGeometry_;
	}
	else
	{
		ar & hasGeom;
	}
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Curve)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);

	bool hasGeom;
	ar& hasGeom;
	if (hasGeom)
	{
		ar & theGeometry_;
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_Curve);