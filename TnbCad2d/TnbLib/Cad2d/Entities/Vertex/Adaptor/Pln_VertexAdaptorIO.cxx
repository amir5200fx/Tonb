#include <Pln_VertexAdaptor.hxx>

#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_VertexAdaptor)
{
	ar << Edges();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_VertexAdaptor)
{
	ar >> ChangeEdges();
}