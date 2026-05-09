#include <MarineRepairSect_Segment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::MarineRepairSect_Segment)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);

	ar & theSegment_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::MarineRepairSect_Segment)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);

	ar & theSegment_;
}