#pragma once
#ifndef _VoyageMesh_FrontInfoAdaptorFwd_Header
#define _VoyageMesh_FrontInfoAdaptorFwd_Header

#include <VoyageMesh_FrontTraits.hxx>

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	template<class FrontTraits>
	class Aft2d_FrontInfoAdaptorTemplate;

	typedef Aft2d_FrontInfoAdaptorTemplate<Aft_FrontTraits<VoyageMesh_Edge>>
		VoyageMesh_FrontInfoAdaptor;
}

#endif // !_VoyageMesh_FrontInfoAdaptorFwd_Header
