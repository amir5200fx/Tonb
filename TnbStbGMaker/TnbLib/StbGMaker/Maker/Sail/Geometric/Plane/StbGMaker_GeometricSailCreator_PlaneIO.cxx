#include <StbGMaker_GeometricSailCreator_Plane.hxx>

#include <Cad2d_Plane.hxx>

DECLARE_SAVE_IMP(tnbLib::stbGmakerLib::GeometricSailCreator_Plane)
{
	ar & boost::serialization::base_object<StbGMaker_GeometricSailCreator>(*this);
	ar & thePlane_;
	ar & theZbar_;
}

DECLARE_LOAD_IMP(tnbLib::stbGmakerLib::GeometricSailCreator_Plane)
{
	ar & boost::serialization::base_object<StbGMaker_GeometricSailCreator>(*this);
	ar & thePlane_;
	ar & theZbar_;
}