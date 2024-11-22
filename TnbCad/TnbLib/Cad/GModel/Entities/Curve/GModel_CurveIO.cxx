#include <GModel_Curve.hxx>

#include <OpenCascade_Serialization.hxx>

#include <opencascade/Geom_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_Curve)
{
	ar & theGeometry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_Curve)
{
	ar & theGeometry_;
}