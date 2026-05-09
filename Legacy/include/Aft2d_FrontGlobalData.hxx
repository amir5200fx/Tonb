#pragma once
#ifndef _Aft2d_FrontGlobalData_Header
#define _Aft2d_FrontGlobalData_Header

#include <Aft_FrontGlobalData.hxx>
#include <Geo_PriorityList.hxx>
#include <Geo_AdTree.hxx>
#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_FrontGlobalDataFwd.hxx>

namespace tnbLib
{

	typedef Geo_PriorityList<std::shared_ptr<Aft2d_Edge>> Aft2d_EdgePriorityList;

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_EdgePriorityList::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_EdgePriorityList::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			);
}


#endif // !_Aft2d_FrontGlobalData_Header