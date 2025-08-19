#pragma once
inline tnbLib::PtdModel_Value::PtdModel_Value()
	: theValue_(0)
	, IsSpecified_(Standard_False)
{
	// empty body [6/3/2021 Amir]
}

inline tnbLib::PtdModel_Value::PtdModel_Value(const Standard_Real x)
	: theValue_(x)
	, IsSpecified_(Standard_True)
{
	// empty body [6/3/2021 Amir]
}