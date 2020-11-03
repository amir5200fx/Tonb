#include <Cad2d_Modeler_Registry.hxx>

#include <Pln_Edge.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Modeler_Registry)
{
	ar & Edges();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Modeler_Registry)
{
	ar & ChangeEdges();
}