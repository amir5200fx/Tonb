#pragma once
#ifndef _Aft2d_FrontAnIsoGlobalDataFwd_Header
#define _Aft2d_FrontAnIsoGlobalDataFwd_Header

#include <Aft2d_EdgeAnIsoFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
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

	typedef Aft_FrontGlobalData<Aft2d_EdgeAnIso, Geo_AdTree, Geo_PriorityList>
		Aft2d_FrontAnIsoGlobalData;
}

#endif // !_Aft2d_FrontAnIsoGlobalDataFwd_Header