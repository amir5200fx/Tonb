#include <Cad2d_Plane_Auxillary.hxx>

#include <Entity2d_Box.hxx>
#include <Geo_Serialization.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Plane_Auxillary)
{
	ar & theBoundingBox_;
	ar & theSystem_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Plane_Auxillary)
{
	ar & theBoundingBox_;
	ar & theSystem_;
}