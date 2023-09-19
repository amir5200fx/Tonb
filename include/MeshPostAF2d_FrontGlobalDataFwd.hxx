#pragma once
#ifndef _MeshPostAF2d_FrontGlobalDataFwd_Header
#define _MeshPostAF2d_FrontGlobalDataFwd_Header

namespace tnbLib
{

	// Forward Declarations [9/1/2023 aamir]
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

	class MeshPostAF2d_Edge;

	typedef Aft_FrontGlobalData<MeshPostAF2d_Edge, Geo_AdTree, Geo_PriorityList>
		MeshPostAF2d_FrontGlobalData;

}

#endif // !_MeshPostAF2d_FrontGlobalDataFwd_Header
