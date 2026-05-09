#include <Geo3d_SpaceCloud_InternalSamples.hxx>

#include <Geo3d_SpaceCloud_TetSamples.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Geo3d_SpaceCloud_InternalSamples)
{
	ar & boost::serialization::base_object<Geo3d_SpaceCloud>(*this);
	ar & theTetSamples_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Geo3d_SpaceCloud_InternalSamples)
{
	ar & boost::serialization::base_object<Geo3d_SpaceCloud>(*this);
	ar & theTetSamples_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Geo3d_SpaceCloud_InternalSamples);