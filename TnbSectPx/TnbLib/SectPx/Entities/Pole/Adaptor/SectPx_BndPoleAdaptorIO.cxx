#include <SectPx_BndPoleAdaptor.hxx>

#include <SectPx_Segment.hxx>
#include <SectPx_TopoSegment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_BndPoleAdaptor)
{
	ar & theSegment_;
	ar & theTopoSegment_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_BndPoleAdaptor)
{
	ar & theSegment_;
	ar & theTopoSegment_;
}