#include <SectPx_Pole.hxx>

Standard_Boolean 
tnbLib::SectPx_Pole::IsInterior() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Pole::IsBoundary() const
{
	return Standard_False;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Pole::RegObjType() const
{
	return sectPxLib::regObjType::pole;
}

Standard_Boolean 
tnbLib::SectPx_Pole::IsPole() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_Pole::IsFrameRegObj() const
{
	return Standard_True;
}