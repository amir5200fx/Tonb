#include <SectPx_InterPoleAdaptor.hxx>

#include <SectPx_Segment.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_InterPoleAdaptor)
{
	ar & theBackward_;
	ar & theForward_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_InterPoleAdaptor)
{
	ar & theBackward_;
	ar & theForward_;
}