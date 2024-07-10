#include <Mesh2d_SizeMapVolume.hxx>

#include <Entity2d_Polygon.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_SizeMapVolume)
{
	ar& boost::serialization::base_object<Global_Indexed>(*this);
	ar& boost::serialization::base_object<Global_Done>(*this);
	ar& theBoundary_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_SizeMapVolume)
{
	ar& boost::serialization::base_object<Global_Indexed>(*this);
	ar& boost::serialization::base_object<Global_Done>(*this);
	ar& theBoundary_;
}