#include <SectPx_InterPoleAdaptor.hxx>

#include <SectPx_Segment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_InterPoleAdaptor)
{
	ar & theBackward_;
	ar & theForward_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_InterPoleAdaptor)
{
	ar & theBackward_;
	ar & theForward_;
}