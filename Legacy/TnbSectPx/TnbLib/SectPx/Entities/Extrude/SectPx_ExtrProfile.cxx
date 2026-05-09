#include <SectPx_ExtrProfile.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::SectPx_ExtrProfile::IsShapeRegObj() const
{
	return Standard_True;
}

Standard_Real 
tnbLib::SectPx_ExtrProfile::Lower() const
{
	Debug_Null_Pointer(Start());
	return Start()->Value();
}

Standard_Real 
tnbLib::SectPx_ExtrProfile::Upper() const
{
	Debug_Null_Pointer(End());
	return End()->Value();
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_ExtrProfile::RegObjType() const
{
	return sectPxLib::regObjType::extrProfile;
}

Standard_Boolean 
tnbLib::SectPx_ExtrProfile::IsExtrProfile() const
{
	return Standard_True;
}