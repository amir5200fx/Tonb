#include <Marine_Model_ProfileAreaSail.hxx>

#include <Geo_ProfileFun.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::Model_ProfileAreaSail)
{
	ar & boost::serialization::base_object<Marine_AreaSailModel>(*this);
	ar & theArea_;
	ar & theZbar_;
}

DECLARE_LOAD_IMP(tnbLib::marineLib::Model_ProfileAreaSail)
{
	ar & boost::serialization::base_object<Marine_AreaSailModel>(*this);
	ar & theArea_;
	ar & theZbar_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_ProfileAreaSail);