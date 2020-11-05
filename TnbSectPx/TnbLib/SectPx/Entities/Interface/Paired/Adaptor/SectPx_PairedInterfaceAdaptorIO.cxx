#include <SectPx_PairedInterfaceAdaptor.hxx>

#include <SectPx_PairedInterface.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_PairedInterfaceAdaptor)
{
	ar & thePair_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_PairedInterfaceAdaptor)
{
	ar & thePair_;
}