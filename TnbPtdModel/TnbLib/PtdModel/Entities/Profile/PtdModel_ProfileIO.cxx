#include <PtdModel_Profile.hxx>

#include <OpenCascade_Serialization.hxx>

#include <Geom2d_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_Profile)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theGeometry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_Profile)
{
	ar & boost::serialization::base_object<PtdModel_Entity>(*this);

	ar & theGeometry_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_Profile);