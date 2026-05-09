#include <Marine_GraphCurve.hxx>

#include <OpenCascade_Serialization.hxx>
#include <Geom2d_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_GraphCurve)
{
	ar & boost::serialization::base_object<Marine_GraphEntity>(*this);
	ar & thePattern_;
	ar & theCurve_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_GraphCurve)
{
	ar & boost::serialization::base_object<Marine_GraphEntity>(*this);
	ar & thePattern_;
	ar & theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Marine_GraphCurve)