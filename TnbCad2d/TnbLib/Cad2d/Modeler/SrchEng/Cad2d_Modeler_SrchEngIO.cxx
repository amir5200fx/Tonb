#include <Cad2d_Modeler_SrchEng.hxx>

#include <Cad2d_Modeler_Corner.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Modeler_SrchEng)
{
	double radius = Radius();
	ar & Corners();
	ar & radius;
	ar & CornerCounter();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Modeler_SrchEng)
{
	ar & ChangeCorners();
	ar & ChangeMaxRadius();
	ar & CornerCounter();
}