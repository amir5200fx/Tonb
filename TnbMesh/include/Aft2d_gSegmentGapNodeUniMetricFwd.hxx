#pragma once
#ifndef _Aft2d_gSegmentGapNodeUniMetricFwd_Header
#define _Aft2d_gSegmentGapNodeUniMetricFwd_Header

#include <Aft2d_gSegmentNodeUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/13/2022 Amir]
	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_gSegmentNodeUniMetric>
		Aft2d_gSegmentGapNodeUniMetric;
}

#endif // !_Aft2d_gSegmentGapNodeUniMetricFwd_Header
