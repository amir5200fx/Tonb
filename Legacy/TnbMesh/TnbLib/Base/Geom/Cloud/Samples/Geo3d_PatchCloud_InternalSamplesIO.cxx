#include <Geo3d_PatchCloud_InternalSamples.hxx>

#include <Geo3d_PatchCloud_EdgeSamples.hxx>
#include <Geo3d_PatchCloud_TriSamples.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Geo3d_PatchCloud_InternalSamples)
{
	ar & boost::serialization::base_object<Geo3d_PatchCloud>(*this);
	ar & theEdgeSamples_;
	ar & theTriSamples_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Geo3d_PatchCloud_InternalSamples)
{
	ar & boost::serialization::base_object<Geo3d_PatchCloud>(*this);
	ar & theEdgeSamples_;
	ar & theTriSamples_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Geo3d_PatchCloud_InternalSamples);