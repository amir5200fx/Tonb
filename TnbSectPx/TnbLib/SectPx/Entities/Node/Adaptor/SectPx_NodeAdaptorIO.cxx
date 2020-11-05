#include <SectPx_NodeAdaptor.hxx>

#include <SectPx_TopoProfile.hxx>
#include <SectPx_Interface.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_NodeAdaptor)
{
	ar & theProfile_;
	ar & theInterface_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_NodeAdaptor)
{
	ar & theProfile_;
	ar & theInterface_;
}