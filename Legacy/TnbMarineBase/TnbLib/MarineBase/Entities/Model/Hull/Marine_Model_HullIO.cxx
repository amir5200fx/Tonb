#include <Marine_Model_Hull.hxx>

#include <Marine_Body_Displacer.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Model_Hull)
{
	ar & boost::serialization::base_object<Marine_Model>(*this);
	ar & theDisplacer_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Model_Hull)
{
	ar & boost::serialization::base_object<Marine_Model>(*this);
	ar & theDisplacer_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_Hull);