#include <Geo3d_SegmentCloud_InternalSamples.hxx>

#include <Geo3d_SegmentCloud_Samples.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Geo3d_SegmentCloud_InternalSamples)
{
	ar & boost::serialization::base_object<Geo3d_SegmentCloud>(*this);
	ar & theSamples_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Geo3d_SegmentCloud_InternalSamples)
{
	ar & boost::serialization::base_object<Geo3d_SegmentCloud>(*this);
	ar & theSamples_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Geo3d_SegmentCloud_InternalSamples);