#include <SectPx_Segment.hxx>

#include <SectPx_Pole.hxx>
#include <SectPx_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_Segment)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & boost::serialization::base_object<SectPx_SegmentAdaptor>(*this);

	ar & theP0_;
	ar & theP1_;

	ar & theEdge_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_Segment)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & boost::serialization::base_object<SectPx_SegmentAdaptor>(*this);

	ar & theP0_;
	ar & theP1_;

	ar & theEdge_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_Segment);