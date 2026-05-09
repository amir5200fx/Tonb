#include <Marine_Model_BodySail.hxx>

#include <Marine_Body_Sail.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Model_BodySail)
{
	ar & boost::serialization::base_object<Model_GeoSail>(*this);
	ar & theBody_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Model_BodySail)
{
	ar & boost::serialization::base_object<Model_GeoSail>(*this);
	ar & theBody_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_BodySail);