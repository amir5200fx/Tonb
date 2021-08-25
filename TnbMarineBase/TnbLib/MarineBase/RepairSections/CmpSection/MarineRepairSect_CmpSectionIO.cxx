#include <MarineRepairSect_CmpSection.hxx>

#include <MarineRepairSect_Section.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::MarineRepairSect_CmpSection)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);
	ar & theSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::MarineRepairSect_CmpSection)
{
	ar & boost::serialization::base_object<Marine_Entity>(*this);
	ar & theSections_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::MarineRepairSect_CmpSection);