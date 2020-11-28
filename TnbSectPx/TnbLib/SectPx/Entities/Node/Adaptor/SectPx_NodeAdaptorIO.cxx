#include <SectPx_NodeAdaptor.hxx>

#include <SectPx_TopoProfile.hxx>
#include <SectPx_Interface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_NodeAdaptor)
{
	ar & theProfile_;
	ar & theInterface_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_NodeAdaptor)
{
	ar & theProfile_;
	ar & theInterface_;
}