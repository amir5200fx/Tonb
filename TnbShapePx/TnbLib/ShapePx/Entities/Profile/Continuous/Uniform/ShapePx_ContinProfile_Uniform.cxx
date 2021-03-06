#include <ShapePx_ContinProfile_Uniform.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::shapePxLib::ContinProfile_Uniform::Value
(
	const Standard_Real x
) const
{
	CheckBoundary(x, FunctionSIG);
	return theValue_;
}

std::vector<typename tnbLib::ShapePx_Profile::offsetPoint> 
tnbLib::shapePxLib::ContinProfile_Uniform::RetrieveOffsets() const
{
	std::vector<offsetPoint> Q;
	Q.reserve(2);

	offsetPoint q0 = { Lower(),LowerValue() };
	offsetPoint q1 = { Upper(),UpperValue() };

	Q.push_back(std::move(q0));
	Q.push_back(std::move(q1));
	return std::move(Q);
}

std::vector<Standard_Real> 
tnbLib::shapePxLib::ContinProfile_Uniform::X() const
{
	std::vector<Standard_Real> xs;
	xs.reserve(2);
	xs.push_back(theX0_);
	xs.push_back(theX1_);
	return std::move(xs);
}

void tnbLib::shapePxLib::ContinProfile_Uniform::Update()
{
	// do nothing
}