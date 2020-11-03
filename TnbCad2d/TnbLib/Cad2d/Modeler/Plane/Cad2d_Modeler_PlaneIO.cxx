#include <Cad2d_Modeler_Plane.hxx>

#include <Cad2d_Plane.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Modeler_Plane)
{
	ar & Planes();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Modeler_Plane)
{
	ar & ChangePlanes();
}