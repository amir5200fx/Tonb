#pragma once
#ifndef _Aft3d_FrontGlobalData_Header
#define _Aft3d_FrontGlobalData_Header

#include <Aft_FrontGlobalData.hxx>
#include <Geo_PriorityList.hxx>
#include <Geo_AdTree.hxx>
#include <Aft3d_FrontGlobalDataFwd.hxx>

namespace tnbLib
{

	typedef Geo_PriorityList<std::shared_ptr<Aft3d_Facet>> Aft3d_FacetPriorityList;

	template<>
	template<>
	TnbMesh_EXPORT void Aft3d_FacetPriorityList::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft3d_FacetPriorityList::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);
}

#endif // !_Aft3d_FrontGlobalData_Header
