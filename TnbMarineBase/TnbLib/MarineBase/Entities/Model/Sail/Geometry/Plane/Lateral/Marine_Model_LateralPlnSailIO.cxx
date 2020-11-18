#include <Marine_Model_LateralPlnSail.hxx>

#include <Cad2d_Plane.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::Model_LateralPlnSail)
{
	ar & boost::serialization::base_object<Marine_PlnSailModel>(*this);
	ar & thePlane_;
	ar & theZbar_;
}

DECLARE_LOAD_IMP(tnbLib::marineLib::Model_LateralPlnSail)
{
	ar & boost::serialization::base_object<Marine_PlnSailModel>(*this);
	ar & thePlane_;
	ar & theZbar_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_LateralPlnSail);