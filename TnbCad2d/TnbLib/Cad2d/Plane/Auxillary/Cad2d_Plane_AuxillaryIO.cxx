#include <Cad2d_Plane_Auxillary.hxx>

#include <Entity2d_Box.hxx>
#include <Geo_Serialization.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Plane_Auxillary)
{
	ar & BoundingBox();
	ar << System();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Plane_Auxillary)
{
	ar & ChangeBoundingBox();
	ar >> ChangeSystem();
}