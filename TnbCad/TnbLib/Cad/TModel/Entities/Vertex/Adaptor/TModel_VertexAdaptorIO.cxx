#include <TModel_VertexAdaptor.hxx>

#include <TModel_Edge.hxx>
#include <TModel_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_VertexAdaptor)
{
	ar & theEdges_;
	ar & theFaces_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_VertexAdaptor)
{
	ar & theEdges_;
	ar & theFaces_;
}