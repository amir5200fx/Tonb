#include <ShapePx_ContinProfile_Linear.hxx>

Standard_Real 
tnbLib::shapePxLib::ContinProfile_Linear::Value
(
	const Standard_Real x
) const
{
	CheckBoundary(x, FunctionSIG);
	const auto x0 = X0();
	const auto x1 = X1();

	const auto y0 = Value0();
	const auto y1 = Value1();
	return (x - x0)*(y1 - y0) / (x1 - x0) + y0;
}