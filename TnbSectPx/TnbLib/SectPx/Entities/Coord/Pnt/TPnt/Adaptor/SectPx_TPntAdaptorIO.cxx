#include <SectPx_TPntAdaptor.hxx>

#include <SectPx_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_TPntAdaptor)
{
	ar & theEdges_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_TPntAdaptor)
{
	ar & theEdges_;
}