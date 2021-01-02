#pragma once
#include <SectPx_RegObj.hxx>
inline Standard_Boolean
tnbLib::SectPx_ObjectRegistry::IsContains
(
	const std::shared_ptr<SectPx_RegObj>& theItem
) const
{
	const auto selected = Find(theItem->Index());
	if (NOT selected)
		return Standard_False;
	if (selected NOT_EQUAL theItem)
		return Standard_False;
	return Standard_True;
}