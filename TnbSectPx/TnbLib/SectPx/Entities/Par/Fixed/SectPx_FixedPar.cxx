#include <SectPx_FixedPar.hxx>

const char* tnbLib::SectPx_FixedPar::typeName_ = "fixed_parameter";

tnbLib::SectPx_FixedPar::SectPx_FixedPar
(
	const Standard_Real theValue,
	const Standard_Real theMin,
	const Standard_Real theMax
)
	: theValue_(theValue, theMin, theMax)
{
	// empty body
}

tnbLib::SectPx_FixedPar::SectPx_FixedPar
(
	const Standard_Integer theIndex,
	const Standard_Real theValue,
	const Standard_Real theMin,
	const Standard_Real theMax
)
	: SectPx_Par(theIndex)
	, theValue_(theValue, theMin, theMax)
{
}

tnbLib::SectPx_FixedPar::SectPx_FixedPar
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Standard_Real theValue,
	const Standard_Real theMin,
	const Standard_Real theMax
)
	: SectPx_Par(theIndex, theName)
	, theValue_(theValue, theMin, theMax)
{
}

tnbLib::word 
tnbLib::SectPx_FixedPar::RegObjTypeName() const
{
	return typeName_;
}

typename tnbLib::sectPxLib::parType 
tnbLib::SectPx_FixedPar::ParType() const
{
	return sectPxLib::parType::fixed;
}

Standard_Boolean 
tnbLib::SectPx_FixedPar::IsFixed() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_FixedPar::IsComplete() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_FixedPar::InCycle() const
{
	return Standard_False;
}

Standard_Real
tnbLib::SectPx_FixedPar::Value() const
{
	return theValue_();
}

void tnbLib::SectPx_FixedPar::SetValue(const Standard_Real x)
{
	theValue_.SetValue(x);
}