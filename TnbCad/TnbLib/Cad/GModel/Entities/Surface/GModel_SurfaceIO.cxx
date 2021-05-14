#include <GModel_Surface.hxx>

#include <GModel_Wire.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_Surface)
{
	ar & boost::serialization::base_object<GModel_Entity>(*this);
	ar & boost::serialization::base_object<GModel_SurfaceGeometry>(*this);

	ar & theOuter_;
	ar & theInner_;

	ar & theOrientation_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_Surface)
{
	ar & boost::serialization::base_object<GModel_Entity>(*this);
	ar & boost::serialization::base_object<GModel_SurfaceGeometry>(*this);

	ar & theOuter_;
	ar & theInner_;

	ar & theOrientation_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GModel_Surface);