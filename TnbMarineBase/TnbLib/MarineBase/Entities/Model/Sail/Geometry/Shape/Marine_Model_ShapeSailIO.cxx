#include <Marine_Model_ShapeSail.hxx>

#include <Marine_Body_Sail.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Model_ShapeSail)
{
	ar & boost::serialization::base_object<Marine_GeoSailModel>(*this);
	ar & theBody_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Model_ShapeSail)
{
	ar & boost::serialization::base_object<Marine_GeoSailModel>(*this);
	ar & theBody_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_ShapeSail);