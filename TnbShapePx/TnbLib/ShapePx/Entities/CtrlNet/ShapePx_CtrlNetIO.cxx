#include <ShapePx_CtrlNet.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::ShapePx_CtrlNet)
{
	ar & theRows_;
	ar & theKnots_;
	ar & theRowDeg_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::ShapePx_CtrlNet)
{
	ar & theRows_;
	ar & theKnots_;
	ar & theRowDeg_;
}