#include <Marine_Model_LateralPlnSail.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Cad2d_Plane.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Model_LateralPlnSail)
{
	ar & boost::serialization::base_object<Model_PlnSail>(*this);
	ar & thePlane_;
	ar & theZbar_;
	ar & theTriangulation_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Model_LateralPlnSail)
{
	ar & boost::serialization::base_object<Model_PlnSail>(*this);
	ar & thePlane_;
	ar & theZbar_;
	ar & theTriangulation_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_LateralPlnSail);