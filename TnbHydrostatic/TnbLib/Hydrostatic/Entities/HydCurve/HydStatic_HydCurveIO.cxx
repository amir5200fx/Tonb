#include <HydStatic_HydCurve.hxx>

#include <OpenCascade_Serialization.hxx>
#include <Geom2d_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_HydCurve)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & theGeom_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_HydCurve)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & theGeom_;
}