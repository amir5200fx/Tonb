#pragma once
#ifndef _Aft3d_FrontInfoFwd_Header
#define _Aft3d_FrontInfoFwd_Header

#include <Aft3d_FrontInfoAdaptorFwd.hxx>
#include <Aft_FrontTraits.hxx>

namespace tnbLib
{

	// Forward Declarations [12/16/2022 Payvand]

	template<class FrontTraits, class FrontAdaptor>
	class Aft3d_FrontInfoTemplate;

	typedef Aft3d_FrontInfoTemplate<Aft_FrontTraits<Aft3d_Facet>, Aft3d_FrontInfoAdaptor>
		Aft3d_FrontInfo;
}

#endif // !_Aft3d_FrontInfoFwd_Header
