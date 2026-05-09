#pragma once
#ifndef _Aft2d_gCornerGapNodeUniMetricFwd_Header
#define _Aft2d_gCornerGapNodeUniMetricFwd_Header

#include <Aft2d_gCornerNodeUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/13/2022 Amir]
	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_gCornerNodeUniMetric>
		Aft2d_gCornerGapNodeUniMetric;
}

#endif // !_Aft2d_gCornerGapNodeUniMetricFwd_Header

