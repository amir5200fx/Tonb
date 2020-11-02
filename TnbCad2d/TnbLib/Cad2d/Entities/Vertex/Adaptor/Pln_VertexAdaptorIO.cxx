#include <Pln_VertexAdaptor.hxx>

#include <Pln_Edge.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_VertexAdaptor)
{
	ar << Edges();
}

DECLARE_LOAD_IMP(tnbLib::Pln_VertexAdaptor)
{
	ar >> ChangeEdges();
}