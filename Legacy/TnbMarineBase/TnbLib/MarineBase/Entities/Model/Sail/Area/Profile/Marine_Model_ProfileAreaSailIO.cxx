#include <Marine_Model_ProfileAreaSail.hxx>

#include <Geo_ProfileFun.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Model_ProfileAreaSail)
{
	ar & boost::serialization::base_object<Model_AreaSail>(*this);
	ar & theArea_;
	ar & theZbar_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Model_ProfileAreaSail)
{
	ar & boost::serialization::base_object<Model_AreaSail>(*this);
	ar & theArea_;
	ar & theZbar_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::Model_ProfileAreaSail);