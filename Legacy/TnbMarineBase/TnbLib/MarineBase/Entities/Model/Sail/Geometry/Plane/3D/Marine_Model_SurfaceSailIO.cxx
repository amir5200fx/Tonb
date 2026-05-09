#include <Marine_Model_SurfaceSail.hxx>

#include <Cad_Shape.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Model_SurfaceSail)
{
	ar & boost::serialization::base_object<Model_PlnSail>(*this);
	ar & theShape_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Model_SurfaceSail)
{
	ar & boost::serialization::base_object<Model_PlnSail>(*this);
	ar & theShape_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_SurfaceSail);