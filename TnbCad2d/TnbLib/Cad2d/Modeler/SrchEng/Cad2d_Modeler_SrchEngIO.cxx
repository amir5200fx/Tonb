#include <Cad2d_Modeler_SrchEng.hxx>

#include <Cad2d_Modeler_Corner.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_SrchEng)
{
	double radius = Radius();
	ar & Corners();
	ar & radius;
	ar & CornerCounter();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_SrchEng)
{
	ar & ChangeCorners();
	ar & ChangeMaxRadius();
	ar & CornerCounter();
}