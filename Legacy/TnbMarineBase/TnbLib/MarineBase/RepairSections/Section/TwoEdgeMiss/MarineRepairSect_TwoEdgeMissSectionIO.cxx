#include <MarineRepairSect_TwoEdgeMissSection.hxx>

#include <MarineRepairSect_HoverSegment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::MarineRepairSect_TwoEdgeMissSection)
{
	ar & boost::serialization::base_object<MarineRepairSect_Section>(*this);
	ar & theSegment0_;
	ar & theSegment1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::MarineRepairSect_TwoEdgeMissSection)
{
	ar & boost::serialization::base_object<MarineRepairSect_Section>(*this);
	ar & theSegment0_;
	ar & theSegment1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::MarineRepairSect_TwoEdgeMissSection);