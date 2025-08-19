#include <Marine_Model_Tank.hxx>

#include <Marine_Body_Tank.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Model_Tank)
{
	ar & boost::serialization::base_object<Marine_Model>(*this);
	ar & theTank_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Model_Tank)
{
	ar & boost::serialization::base_object<Marine_Model>(*this);
	ar & theTank_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_Tank);