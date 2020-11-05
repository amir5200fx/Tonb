#include <SectPx_TPntAdaptor.hxx>

#include <SectPx_Edge.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_TPntAdaptor)
{
	ar & theEdges_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_TPntAdaptor)
{
	ar & theEdges_;
}