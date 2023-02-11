#pragma once
#ifndef _Aft2d_SegmentGapEdgeUniMetricFwd_Header
#define _Aft2d_SegmentGapEdgeUniMetricFwd_Header

#include <Aft2d_SegmentEdgeUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class BndEdgeType>
	class Aft2d_GapEdgeTemplate;

	typedef Aft2d_GapEdgeTemplate<Aft2d_SegmentEdgeUniMetric>
		Aft2d_SegmentGapEdgeUniMetric;
}

#endif // !_Aft2d_SegmentGapEdgeUniMetricFwd_Header
