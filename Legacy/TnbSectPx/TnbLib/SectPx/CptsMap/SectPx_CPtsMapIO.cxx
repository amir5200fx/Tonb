#include <SectPx_CPtsMap.hxx>

#include <SectPx_Pole.hxx>
#include <SectPx_Segment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_CPtsMap)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);
	ar & theSegment_;
	ar & theSense_;
	ar & theP0_;
	ar & theP1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_CPtsMap)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);
	ar & theSegment_;
	ar & theSense_;
	ar & theP0_;
	ar & theP1_;
}