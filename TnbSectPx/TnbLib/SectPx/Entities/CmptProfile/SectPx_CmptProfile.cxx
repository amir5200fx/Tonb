#include <SectPx_CmptProfile.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::SectPx_CmptProfile::typeName_("composite profile");

Standard_Boolean 
tnbLib::SectPx_CmptProfile::IsCmptProfile() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_CmptProfile::IsFrameRegObj() const
{
	return Standard_True;
}

tnbLib::word 
tnbLib::SectPx_CmptProfile::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_CmptProfile::RegObjType() const
{
	return sectPxLib::regObjType::cmptProfile;
}