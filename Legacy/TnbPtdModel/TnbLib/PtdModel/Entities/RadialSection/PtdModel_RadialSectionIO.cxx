#include <PtdModel_RadialSection.hxx>

#include <OpenCascade_Serialization.hxx>

#include <Geom2d_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_RadialSection)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);
	ar & theCurves_;
	ar & theRadius_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_RadialSection)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);
	ar & theCurves_;
	ar & theRadius_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_RadialSection);