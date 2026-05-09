#pragma once
#ifndef _MeshPostAF2d_FrontInfoFwd_Header
#define _MeshPostAF2d_FrontInfoFwd_Header

#include <MeshPostAF2d_FrontInfoAdaptorFwd.hxx>
#include <MeshPostAF2d_MetricPrcsrFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/1/2023 aamir]
	template<class FrontTraits, class FrontAdaptor>
	class Aft2d_FrontInfoTemplate;

	template<class FrontType>
	struct Aft_FrontTraits;

	class MeshPostAF2d_Element;
	class MeshPostAF2d_Edge;

	typedef Aft2d_FrontInfoTemplate<Aft_FrontTraits<MeshPostAF2d_Edge>, MeshPostAF2d_FrontInfoAdaptor>
		MeshPostAF2d_FrontInfo;
}

#endif // !_MeshPostAF2d_FrontInfoFwd_Header
