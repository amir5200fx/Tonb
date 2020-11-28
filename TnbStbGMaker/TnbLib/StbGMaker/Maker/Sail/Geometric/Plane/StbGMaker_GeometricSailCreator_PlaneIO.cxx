#include <StbGMaker_GeometricSailCreator_Plane.hxx>

#include <Cad2d_Plane.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::stbGmakerLib::GeometricSailCreator_Plane)
{
	ar & boost::serialization::base_object<StbGMaker_GeometricSailCreator>(*this);
	ar & thePlane_;
	ar & theZbar_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::stbGmakerLib::GeometricSailCreator_Plane)
{
	ar & boost::serialization::base_object<StbGMaker_GeometricSailCreator>(*this);
	ar & thePlane_;
	ar & theZbar_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::stbGmakerLib::GeometricSailCreator_Plane);