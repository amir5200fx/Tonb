#pragma once
#ifndef _Aft3d_FrontInfoAdaptorFwd_Header
#define _Aft3d_FrontInfoAdaptorFwd_Header

#include <Aft_FrontTraits.hxx>
#include <Aft3d_FacetFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/15/2022 Payvand]

	template<class FrontTraits>
	class Aft3d_FrontInfoAdaptorTemplate;

	typedef Aft3d_FrontInfoAdaptorTemplate<Aft_FrontTraits<Aft3d_Facet>>
		Aft3d_FrontInfoAdaptor;
}

#endif // !_Aft3d_FrontInfoAdaptorFwd_Header
