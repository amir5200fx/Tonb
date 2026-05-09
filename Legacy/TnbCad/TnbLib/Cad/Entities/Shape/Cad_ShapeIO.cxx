#include <Cad_Shape.hxx>

#include <OpenCascade_Serialization.hxx>
#include <Entity3d_Box.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_Shape)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theShape_;
	ar & theBoundingBox_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_Shape)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theShape_;
	ar & theBoundingBox_;
}