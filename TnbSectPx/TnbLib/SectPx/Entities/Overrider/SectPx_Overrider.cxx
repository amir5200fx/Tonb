#include <SectPx_Overrider.hxx>

Standard_Boolean 
tnbLib::SectPx_Overrider::IsOverrider() const
{
	return Standard_True;
}

tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Overrider::RegObjType() const
{
	return sectPxLib::regObjType::overrider;
}