#include <SectPx_Pnt.hxx>

Standard_Boolean 
tnbLib::SectPx_Pnt::IsInner() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Pnt::IsOuter() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Pnt::IsMaster() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Pnt::IsSlave() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_Pnt::IsPnt() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_Pnt::IsFrameRegObj() const
{
	return Standard_True;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Pnt::RegObjType() const
{
	return sectPxLib::regObjType::pnt;
}