#include <GModel_ParaCurve.hxx>

#include <OpenCascade_Serialization.hxx>

#include <Geom2d_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_ParaCurve)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theGeometry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_ParaCurve)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theGeometry_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GModel_ParaCurve);