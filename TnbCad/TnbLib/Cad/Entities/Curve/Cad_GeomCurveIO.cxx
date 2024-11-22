#include <Cad_GeomCurve.hxx>

#include <OpenCascade_Serialization.hxx>
#include <opencascade/Geom_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_GeomCurve)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theGeometry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_GeomCurve)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theGeometry_;
}