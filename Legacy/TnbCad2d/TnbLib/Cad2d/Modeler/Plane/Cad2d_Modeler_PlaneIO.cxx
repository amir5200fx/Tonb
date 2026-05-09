#include <Cad2d_Modeler_Plane.hxx>

#include <Cad2d_Plane.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Plane)
{
	ar & Planes();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Plane)
{
	ar & ChangePlanes();
}