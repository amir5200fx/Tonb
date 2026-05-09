#include <ShapePx_ContinProfile_GeneratedCustom.hxx>

#include <OpenCascade_Serialization.hxx>
#include <SectPx_CurveQ.hxx>
#include <Geom2d_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::shapePxLib::ContinProfile_GeneratedCustom)
{
	ar & boost::serialization::base_object<ContinProfile_Custom>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theDegree_;
	ar & theCurve_;

	ar & theProfile_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::shapePxLib::ContinProfile_GeneratedCustom)
{
	ar & boost::serialization::base_object<ContinProfile_Custom>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theDegree_;
	ar & theCurve_;

	ar & theProfile_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::shapePxLib::ContinProfile_GeneratedCustom);
