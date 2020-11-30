//#pragma once
//#include <SectPx_RegObj.hxx>
//
//inline Standard_Boolean 
//tnbLib::SectPx_Registry::IsContains
//(
//	const std::shared_ptr<SectPx_RegObj>& theItem
//) const
//{
//	const auto selected = Find(theItem->Index());
//	if (NOT selected)
//		return Standard_False;
//	if (selected NOT_EQUAL theItem) 
//		return Standard_False;
//	return Standard_True;
//}
//
//
//inline Standard_Boolean
//tnbLib::SectPx_Registry::Next
//(
//	typename std::map<Standard_Integer, std::shared_ptr<SectPx_RegObj>>::iterator & it,
//	const sectPxLib::regObjType t
//) const
//{
//	Debug_If_Condition(it IS_EQUAL theObjects_.end());
//	while (it NOT_EQUAL theObjects_.end() AND it->second->RegObjType() NOT_EQUAL t)
//	{
//		it++;
//	}
//	if (it NOT_EQUAL theObjects_.end())
//	{
//		return Standard_False;
//	}
//	return Standard_True;
//}