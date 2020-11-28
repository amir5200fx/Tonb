#include <Cad2d_Modeler_SelectList.hxx>

#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_SelectList)
{
	ar & Items();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_SelectList)
{
	ar & ChangeItems();
}