#pragma once
#ifndef _VoyageMesh_FrontInfoFwd_Header
#define _VoyageMesh_FrontInfoFwd_Header

#include <VoyageMesh_FrontInfoAdaptorFwd.hxx>
#include <VoyageMesh_MetricPrcsr.hxx>

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	template<class FrontTraits, class FrontAdaptor>
	class Aft2d_FrontInfoTemplate;

	template<class FrontType>
	struct Aft_FrontTraits;

	class VoyageMesh_Element;
	class VoyageMesh_Edge;

	typedef Aft2d_FrontInfoTemplate<Aft_FrontTraits<VoyageMesh_Edge>, VoyageMesh_FrontInfoAdaptor>
		VoyageMesh_FrontInfo;
}

#endif // !_VoyageMesh_FrontInfoFwd_Header
