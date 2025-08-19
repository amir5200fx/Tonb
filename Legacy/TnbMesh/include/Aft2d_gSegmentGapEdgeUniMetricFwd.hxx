#pragma once
#ifndef _Aft2d_gSegmentGapEdgeUniMetricFwd_Header
#define _Aft2d_gSegmentGapEdgeUniMetricFwd_Header

#include <Aft2d_gSegmentEdgeUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/12/2022 Amir]
	template<class BndEdgeType>
	class Aft2d_GapEdgeTemplate;

	typedef Aft2d_GapEdgeTemplate<Aft2d_gSegmentEdgeUniMetric>
		Aft2d_gSegmentGapEdgeUniMetric;
}

#endif // !_Aft2d_gSegmentGapEdgeUniMetricFwd_Header
