#include <Model_ParamProfile.hxx>

Standard_Real 
tnbLib::Model_ParamProfile::LowerValue() const
{
	return Value(Lower());
}

Standard_Real 
tnbLib::Model_ParamProfile::UpperValue() const
{
	return Value(Upper());
}

Standard_Boolean 
tnbLib::Model_ParamProfile::InsideSpan
(
	const Standard_Real x
) const
{
	return x <= Upper() && x >= Lower();
}

std::vector<Standard_Real> 
tnbLib::Model_ParamProfile::Breacks() const
{
	std::vector<Standard_Real> xs;
	xs.reserve(2);
	xs.push_back(Lower());
	xs.push_back(Upper());
	return std::move(xs);
}