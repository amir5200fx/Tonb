#include <SectPx_Datum.hxx>

Standard_Boolean 
tnbLib::SectPx_Datum::IsDatum() const
{
	return Standard_True;
}

typename tnbLib::sectPxLib::regObjType
tnbLib::SectPx_Datum::RegObjType() const
{
	return sectPxLib::regObjType::datum;
}