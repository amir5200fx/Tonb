#pragma once
#ifndef _Aft2d_OptNodeSurface_AnalyticalFwd_Header
#define _Aft2d_OptNodeSurface_AnalyticalFwd_Header

#include <Aft2d_EdgeSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/5/2022 Amir]
	template<class FrontType, class MetricType>
	class Aft_OptNode_Analytical;

	class Entity2d_Metric1;

	typedef Aft_OptNode_Analytical<Aft2d_EdgeSurface, Entity2d_Metric1>
		Aft2d_OptNodeSurface_Analytical;
}

#endif // !_Aft2d_OptNodeSurface_AnalyticalFwd_Header
