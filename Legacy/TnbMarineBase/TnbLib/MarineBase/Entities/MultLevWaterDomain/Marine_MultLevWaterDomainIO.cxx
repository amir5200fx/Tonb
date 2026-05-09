#include <Marine_MultLevWaterDomain.hxx>

#include <Marine_WaterDomain.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Body.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_MultLevWaterDomain)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);
	ar & theDomain_;
	ar & theWaters_;
	ar & theBody_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_MultLevWaterDomain)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);
	ar & theDomain_;
	ar & theWaters_;
	ar & theBody_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Marine_MultLevWaterDomain);