#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
inline void tnbLib::PtdModel_BndValue::Check
(
	const Standard_Real theLower,
	const Standard_Real theUpper
)
{
	if (theUpper < theLower)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid values for the lower and upper bound has been detected!" << endl
			<< "- lower: " << theLower << endl
			<< "- upper:" << theUpper << endl
			<< abort(FatalError);
	}
}

inline tnbLib::PtdModel_BndValue::PtdModel_BndValue
(
	const Standard_Real theLower, 
	const Standard_Real theUpper
)
	: theLower_(theLower)
	, theUpper_(theUpper)
{
	Check(Lower(), Upper());
}

inline tnbLib::PtdModel_BndValue::PtdModel_BndValue
(
	const Standard_Real theLower,
	const Standard_Real theUpper,
	const Standard_Real x
)
	: PtdModel_Value(x)
	, theLower_(theLower)
	, theUpper_(theUpper)
{
	Check(Lower(), Upper());
	SetValue(x);
}

inline Standard_Boolean 
tnbLib::PtdModel_BndValue::IsNull() const
{
	return (Upper() - Lower()) IS_EQUAL 0;
}

inline Standard_Boolean 
tnbLib::PtdModel_BndValue::IsInside(const Standard_Real x) const
{
	return INSIDE(x, Lower(), Upper());
}

inline tnbLib::PtdModel_BndValue 
tnbLib::PtdModel_BndValue::NormalizedValue(const Standard_Real x)
{
	PtdModel_BndValue v(0, 1, x);
	return std::move(v);
}