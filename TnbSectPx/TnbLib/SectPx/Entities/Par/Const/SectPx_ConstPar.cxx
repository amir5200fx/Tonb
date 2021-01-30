#include <SectPx_ConstPar.hxx>

const char* tnbLib::SectPx_ConstPar::typeName_("const_parameter");

tnbLib::SectPx_ConstPar::SectPx_ConstPar(const Standard_Real theValue)
	: theValue_(theValue)
{
}

tnbLib::SectPx_ConstPar::SectPx_ConstPar
(
	const Standard_Integer theIndex, 
	const Standard_Real theValue
)
	: SectPx_Par(theIndex)
	, theValue_(theValue)
{
}

tnbLib::SectPx_ConstPar::SectPx_ConstPar
(
	const Standard_Integer theIndex, 
	const word & theName,
	const Standard_Real theValue
)
	: SectPx_Par(theIndex, theName)
	, theValue_(theValue)
{
}

tnbLib::word 
tnbLib::SectPx_ConstPar::RegObjTypeName() const
{
	return typeName_;
}

typename tnbLib::sectPxLib::parType 
tnbLib::SectPx_ConstPar::ParType() const
{
	return sectPxLib::parType::constant;
}

Standard_Boolean 
tnbLib::SectPx_ConstPar::IsConstant() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_ConstPar::IsComplete() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_ConstPar::InCycle() const
{
	return Standard_False;
}

Standard_Real 
tnbLib::SectPx_ConstPar::Value() const
{
	return theValue_;
}

void tnbLib::SectPx_ConstPar::SetValue(const Standard_Real x)
{
	theValue_ = x;
}