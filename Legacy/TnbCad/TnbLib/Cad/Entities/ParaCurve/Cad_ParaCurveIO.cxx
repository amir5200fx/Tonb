#include <Cad_ParaCurve.hxx>

#include <OpenCascade_Serialization.hxx>

#include <opencascade/Geom2d_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_ParaCurve)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theGeometry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_ParaCurve)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theGeometry_;
}
