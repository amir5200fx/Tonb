#pragma once
#ifndef _MeshPostAF2d_FrontInfoAdaptorFwd_Header
#define _MeshPostAF2d_FrontInfoAdaptorFwd_Header

#include <MeshPostAF2d_FrontTraits.hxx>

namespace tnbLib
{

	// Forward Declarations [9/1/2023 aamir]
	template<class FrontTraits>
	class Aft2d_FrontInfoAdaptorTemplate;

	typedef Aft2d_FrontInfoAdaptorTemplate<Aft_FrontTraits<MeshPostAF2d_Edge>>
		MeshPostAF2d_FrontInfoAdaptor;
}

#endif // !_MeshPostAF2d_FrontInfoAdaptorFwd_Header
