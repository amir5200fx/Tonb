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

std::vector<typename tnbLib::ShapePx_Profile::offsetPoint>
tnbLib::shapePxLib::ContinProfile_Linear::RetrieveOffsets() const
{
	std::vector<offsetPoint> Q;
	Q.reserve(2);

	Q.push_back(theQ0_);
	Q.push_back(theQ1_);
	return std::move(Q);
}

std::vector<Standard_Real> 
tnbLib::shapePxLib::ContinProfile_Linear::X() const
{
	std::vector<Standard_Real> xs;
	xs.reserve(2);
	xs.push_back(theQ0_.x);
	xs.push_back(theQ0_.y);
	return std::move(xs);
}

void tnbLib::shapePxLib::ContinProfile_Linear::Update()
{
	// do nothing
}