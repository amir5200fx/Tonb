#include <Cad2d_Plane_Manager.hxx>

#include <Cad_EntityManager.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Plane_Manager)
{
	ar & theVertices_;
	ar & theEdges_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Plane_Manager)
{
	ar & theVertices_;
	ar & theEdges_;
}