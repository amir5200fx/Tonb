#pragma once
#include <Global_Tools.hxx>
template<class ShapeType>
inline std::shared_ptr<tnbLib::Mesh_Curve_Info> 
tnbLib::Aft2d_SolutionDataSurface<ShapeType>::CurveInfo
(
	const Standard_Integer theSurfId
) const
{
	auto item = Global_Tools::Find(theCurveInfo_, theSurfId);
	return std::move(item);
}

template<class ShapeType>
inline void tnbLib::Aft2d_SolutionDataSurface<ShapeType>::SetCurveInfo
(
	const Standard_Integer theSurfId, 
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
)
{
	Global_Tools::Insert(theSurfId, theInfo, theCurveInfo_);
}

template<class ShapeType>
inline void tnbLib::Aft2d_SolutionDataSurface<ShapeType>::SetCurveInfo
(
	const Standard_Integer theSurfId,
	std::shared_ptr<Mesh_Curve_Info>&& theInfo
)
{
	Global_Tools::Insert(theSurfId, std::move(theInfo), theCurveInfo_);
}