#pragma once
#ifndef _Aft3d_FrontGlobalDataFwd_Header
#define _Aft3d_FrontGlobalDataFwd_Header

#include <Aft3d_FacetFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/14/2022 Payvand]

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

	typedef Aft_FrontGlobalData<Aft3d_Facet, Geo_AdTree, Geo_PriorityList>
		Aft3d_FrontGlobalData;
}

#endif // !_Aft3d_FrontGlobalDataFwd_Header
