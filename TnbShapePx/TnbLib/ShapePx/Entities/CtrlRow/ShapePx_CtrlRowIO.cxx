#include <ShapePx_CtrlRow.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_CtrlRow)
{
	ar & thePnts_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_CtrlRow)
{
	ar & thePnts_;
}