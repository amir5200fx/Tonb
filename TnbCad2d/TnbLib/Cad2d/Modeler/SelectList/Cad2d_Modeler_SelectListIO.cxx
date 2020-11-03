#include <Cad2d_Modeler_SelectList.hxx>

#include <Pln_Edge.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Modeler_SelectList)
{
	ar & Items();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Modeler_SelectList)
{
	ar & ChangeItems();
}