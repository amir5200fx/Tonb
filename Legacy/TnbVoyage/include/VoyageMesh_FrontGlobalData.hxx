#pragma once
#ifndef _VoyageMesh_FrontGlobalData_Header
#define _VoyageMesh_FrontGlobalData_Header

#include <VoyageMesh_FrontGlobalDataFwd.hxx>
#include <VoyageMesh_Edge.hxx>
#include <Aft_FrontGlobalData.hxx>
#include <Geo_PriorityList.hxx>
#include <Geo_AdTree.hxx>

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	class VoyageMesh_Edge;

	typedef Geo_PriorityList<std::shared_ptr<VoyageMesh_Edge>>
		VoyageMesh_EdgePriorityList;

}

#endif // !_VoyageMesh_FrontGlobalData_Header
