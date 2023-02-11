#pragma once
#ifndef _Aft2d_SegmentGapNodeUniMetricFwd_Header
#define _Aft2d_SegmentGapNodeUniMetricFwd_Header

#include <Aft2d_SegmentNodeUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_SegmentNodeUniMetric>
		Aft2d_SegmentGapNodeUniMetric;
}

#endif // !_Aft2d_SegmentGapNodeUniMetricFwd_Header
