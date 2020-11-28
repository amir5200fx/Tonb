#include <SectPx_BndPoleAdaptor.hxx>

#include <SectPx_Segment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_BndPoleAdaptor)
{
	ar & theSegment_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_BndPoleAdaptor)
{
	ar & theSegment_;
}