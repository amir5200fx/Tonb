#pragma once
#ifndef _MeshPostAF2d_FrontGlobalData_Header
#define _MeshPostAF2d_FrontGlobalData_Header

#include <MeshPostAF2d_FrontGlobalDataFwd.hxx>
#include <MeshPostAF2d_Edge.hxx>
#include <Aft_FrontGlobalData.hxx>
#include <Geo_PriorityList.hxx>
#include <Geo_AdTree.hxx>

namespace tnbLib
{

	// Forward Declarations [9/1/2023 aamir]
	class MeshPostAF2d_Edge;

	typedef Geo_PriorityList<std::shared_ptr<MeshPostAF2d_Edge>>
		MeshPostAF2d_EdgePriorityList;

}

#endif // !_MeshPostAF2d_FrontGlobalData_Header
