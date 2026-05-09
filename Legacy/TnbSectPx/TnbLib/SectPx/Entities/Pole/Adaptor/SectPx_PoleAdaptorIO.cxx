#include <SectPx_PoleAdaptor.hxx>

#include <SectPx_TopoProfile.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_PoleAdaptor)
{
	ar & theProfile_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_PoleAdaptor)
{
	ar & theProfile_;
}