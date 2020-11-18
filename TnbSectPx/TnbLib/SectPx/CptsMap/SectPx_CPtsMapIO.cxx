#include <SectPx_CPtsMap.hxx>

#include <SectPx_Pole.hxx>
#include <SectPx_Segment.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_CPtsMap)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);
	ar & theSegment_;
	ar & theSense_;
	ar & theP0_;
	ar & theP1_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_CPtsMap)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);
	ar & theSegment_;
	ar & theSense_;
	ar & theP0_;
	ar & theP1_;
}