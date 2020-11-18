#include <Marine_Model_Tank.hxx>

#include <Marine_Body_Tank.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::Model_Tank)
{
	ar & boost::serialization::base_object<Marine_Model>(*this);
	ar & theTank_;
}

DECLARE_LOAD_IMP(tnbLib::marineLib::Model_Tank)
{
	ar & boost::serialization::base_object<Marine_Model>(*this);
	ar & theTank_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_Tank);