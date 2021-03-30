#include <TModel_Surface.hxx>

#include <TModel_Wire.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Surface)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<TModel_SurfaceGeometry>(*this);

	ar & theOuter_;
	ar & theInner_;

	ar & theParaBoundingBox_;
	ar & theBoundingBox_;

	ar & theOrientation_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Surface)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<TModel_SurfaceGeometry>(*this);

	ar & theOuter_;
	ar & theInner_;

	ar & theParaBoundingBox_;
	ar & theBoundingBox_;

	ar & theOrientation_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_Surface);