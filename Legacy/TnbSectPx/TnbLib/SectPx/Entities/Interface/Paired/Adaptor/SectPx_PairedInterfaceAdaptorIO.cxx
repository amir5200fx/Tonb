#include <SectPx_PairedInterfaceAdaptor.hxx>

#include <SectPx_PairedInterface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_PairedInterfaceAdaptor)
{
	ar & thePair_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_PairedInterfaceAdaptor)
{
	ar & thePair_;
}