#include <SectPx_EmptyInterface.hxx>

const char* tnbLib::SectPx_EmptyInterface::typeName_("empty interface");

Standard_Boolean 
tnbLib::SectPx_EmptyInterface::IsEmpty() const
{
	return Standard_True;
}

tnbLib::word 
tnbLib::SectPx_EmptyInterface::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::sectPxLib::interfaceType 
tnbLib::SectPx_EmptyInterface::InterfaceType() const
{
	return sectPxLib::interfaceType::empty;
}

void tnbLib::SectPx_EmptyInterface::disJoint()
{
	SetNode(nullptr);
}

Standard_Boolean 
tnbLib::SectPx_EmptyInterface::IsRemovable() const
{
	return NOT Node();
}