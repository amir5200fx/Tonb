#include <Marine_Model_Hull.hxx>

#include <Marine_Body_Displacer.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::Model_Hull)
{
	ar & boost::serialization::base_object<Marine_Model>(*this);
	ar & theDisplacer_;
}