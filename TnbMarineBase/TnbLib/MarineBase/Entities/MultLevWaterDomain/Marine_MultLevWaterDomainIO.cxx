#include <Marine_MultLevWaterDomain.hxx>

#include <Marine_WaterDomain.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_MultLevWaterDomain)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);
	ar & theDomains_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_MultLevWaterDomain)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);
	ar & theDomains_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Marine_MultLevWaterDomain);