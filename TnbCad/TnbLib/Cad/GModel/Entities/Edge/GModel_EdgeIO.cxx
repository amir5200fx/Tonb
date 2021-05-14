#include <GModel_Edge.hxx>

#include <GModel_ParaCurve.hxx>
#include <GModel_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_Edge)
{
	ar & thePar_;
	ar & theCurve_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_Edge)
{
	ar & thePar_;
	ar & theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GModel_Edge);