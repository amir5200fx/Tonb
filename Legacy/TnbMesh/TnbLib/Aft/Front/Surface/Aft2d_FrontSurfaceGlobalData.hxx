#pragma once
#ifndef _Aft2d_FrontSurfaceGlobalData_Header
#define _Aft2d_FrontSurfaceGlobalData_Header

#include <Aft_FrontGlobalData.hxx>
#include <Geo_PriorityList.hxx>
#include <Geo_AdTree.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft2d_FrontSurfaceGlobalDataFwd.hxx>

namespace tnbLib
{

	typedef Geo_PriorityList<std::shared_ptr<Aft2d_EdgeSurface>> Aft2d_EdgeSurfacePriorityList;

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_EdgeSurfacePriorityList::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_EdgeSurfacePriorityList::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);
}

#endif // !_Aft2d_FrontSurfaceGlobalData_Header