#pragma once
#ifndef _VoyageMesh_FrontGlobalDataFwd_Header
#define _VoyageMesh_FrontGlobalDataFwd_Header

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	template
		<
		class FrontEntity,
		template<class> class GeomSearch,
		template<class> class PriorityList
		>
		class Aft_FrontGlobalData;

	template<class T>
	class Geo_AdTree;

	template<class T>
	class Geo_PriorityList;

	class VoyageMesh_Edge;

	typedef Aft_FrontGlobalData<VoyageMesh_Edge, Geo_AdTree, Geo_PriorityList>
		VoyageMesh_FrontGlobalData;
}

#endif // !_VoyageMesh_FrontGlobalDataFwd_Header
