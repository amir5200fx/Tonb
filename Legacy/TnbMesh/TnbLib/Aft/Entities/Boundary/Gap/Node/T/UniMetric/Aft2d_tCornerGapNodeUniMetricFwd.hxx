#pragma once
#ifndef _Aft2d_tCornerGapNodeUniMetricFwd_Header
#define _Aft2d_tCornerGapNodeUniMetricFwd_Header

#include <Aft2d_tCornerNodeUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/20/2022 Amir]
	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_tCornerNodeUniMetric>
		Aft2d_tCornerGapNodeUniMetric;
}

#endif // !_Aft2d_tCornerGapNodeUniMetricFwd_Header
