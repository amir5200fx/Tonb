#include <SectPx_RegObj.hxx>

Standard_Boolean 
tnbLib::SectPx_RegObj::IsParent() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_RegObj::IsChild() const
{
	return Standard_False;
}

Standard_Boolean
tnbLib::SectPx_RegObj::IsEdge() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_RegObj::IsSegment() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_RegObj::IsPole() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_RegObj::IsInterface() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_RegObj::IsNode() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_RegObj::IsProfile() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_RegObj::IsCmptProfile() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_RegObj::IsFrame() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::SectPx_RegObj::IsOverrider() const
{
	return Standard_False;
}