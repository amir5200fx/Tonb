#include <Marine_MultLevWaterDomain.hxx>

#include <Marine_WaterDomain.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_MultLevWaterDomain)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);
	ar & theDomains_;
}

DECLARE_LOAD_IMP(tnbLib::Marine_MultLevWaterDomain)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);
	ar & theDomains_;
}