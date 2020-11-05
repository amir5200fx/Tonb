#include <SectPx_BndPoleAdaptor.hxx>

#include <SectPx_Segment.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_BndPoleAdaptor)
{
	ar & theSegment_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_BndPoleAdaptor)
{
	ar & theSegment_;
}