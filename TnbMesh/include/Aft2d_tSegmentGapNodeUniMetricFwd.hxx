#pragma once
#ifndef _Aft2d_tSegmentGapNodeUniMetricFwd_Header
#define _Aft2d_tSegmentGapNodeUniMetricFwd_Header

#include <Aft2d_tSegmentNodeUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/20/2022 Amir]
	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_tSegmentNodeUniMetric>
		Aft2d_tSegmentGapNodeUniMetric;
}

#endif // !_Aft2d_tSegmentGapNodeUniMetricFwd_Header
