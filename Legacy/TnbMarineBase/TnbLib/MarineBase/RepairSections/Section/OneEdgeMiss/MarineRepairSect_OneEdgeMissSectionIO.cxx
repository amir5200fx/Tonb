#include <MarineRepairSect_OneEdgeMissSection.hxx>

#include <MarineRepairSect_CrossSegment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::MarineRepairSect_OneEdgeMissSection)
{
	ar & boost::serialization::base_object<MarineRepairSect_Section>(*this);

	ar & theSegment_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::MarineRepairSect_OneEdgeMissSection)
{
	ar & boost::serialization::base_object<MarineRepairSect_Section>(*this);

	ar & theSegment_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::MarineRepairSect_OneEdgeMissSection);