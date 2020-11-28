#include <Marine_Model_LateralPlnSail.hxx>

#include <Cad2d_Plane.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Model_LateralPlnSail)
{
	ar & boost::serialization::base_object<Marine_PlnSailModel>(*this);
	ar & thePlane_;
	ar & theZbar_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Model_LateralPlnSail)
{
	ar & boost::serialization::base_object<Marine_PlnSailModel>(*this);
	ar & thePlane_;
	ar & theZbar_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_LateralPlnSail);