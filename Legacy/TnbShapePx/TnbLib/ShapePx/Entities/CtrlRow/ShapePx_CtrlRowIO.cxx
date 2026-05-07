#include <ShapePx_CtrlRow.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_CtrlRow)
{
	ar & thePnts_;
	ar & theX_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_CtrlRow)
{
	ar & thePnts_;
	ar & theX_;
}