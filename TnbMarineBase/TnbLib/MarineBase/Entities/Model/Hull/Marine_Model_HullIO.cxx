#include <Marine_Model_Hull.hxx>

#include <Marine_Body_Displacer.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::Model_Hull)
{
	ar & boost::serialization::base_object<Marine_Model>(*this);
	ar & theDisplacer_;
}

DECLARE_LOAD_IMP(tnbLib::marineLib::Model_Hull)
{
	ar & boost::serialization::base_object<Marine_Model>(*this);
	ar & theDisplacer_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_Hull);