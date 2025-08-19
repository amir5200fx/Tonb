#pragma once
#ifndef _Aft2d_CornerGapNodeUniMetricFwd_Header
#define _Aft2d_CornerGapNodeUniMetricFwd_Header

#include <Aft2d_CornerNodeUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_CornerNodeUniMetric>
		Aft2d_CornerGapNodeUniMetric;
}

#endif // !_Aft2d_CornerGapNodeUniMetricFwd_Header
