#include <Cad2d_Plane_Manager.hxx>

#include <Cad_EntityManager.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Plane_Manager)
{
	ar << Corners();
	ar << Segments();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Plane_Manager)
{
	ar >> ChangeCorners();
	ar >> ChangeSegments();
}