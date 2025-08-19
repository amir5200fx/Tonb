#include <Cad2d_Modeler_Registry.hxx>

#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Registry)
{
	ar & Edges();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Registry)
{
	ar & ChangeEdges();
}