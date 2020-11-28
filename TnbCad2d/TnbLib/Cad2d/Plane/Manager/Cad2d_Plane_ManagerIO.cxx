#include <Cad2d_Plane_Manager.hxx>

#include <Cad_EntityManager.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Plane_Manager)
{
	ar << Corners();
	ar << Segments();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Plane_Manager)
{
	ar >> ChangeCorners();
	ar >> ChangeSegments();
}