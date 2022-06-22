#pragma once
#ifndef _Aft2d_tSegmentGapEdgeUniMetricFwd_Header
#define _Aft2d_tSegmentGapEdgeUniMetricFwd_Header

#include <Aft2d_tSegmentEdgeUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/20/2022 Amir]
	template<class BndEdgeType>
	class Aft2d_GapEdgeTemplate;

	typedef Aft2d_GapEdgeTemplate<Aft2d_tSegmentEdgeUniMetric>
		Aft2d_tSegmentGapEdgeUniMetric;
}

#endif // !_Aft2d_tSegmentGapEdgeUniMetricFwd_Header
