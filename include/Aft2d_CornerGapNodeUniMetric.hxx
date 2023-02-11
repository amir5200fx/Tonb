#pragma once
#ifndef _Aft2d_CornerGapNodeUniMetric_Header
#define _Aft2d_CornerGapNodeUniMetric_Header

#include <Aft2d_CornerGapNodeUniMetricFwd.hxx>
#include <Aft2d_GapNodeTemplate.hxx>
#include <Aft2d_CornerNodeUniMetric.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::shared_ptr<Aft2d_BndEdgeAnIso>
		Aft2d_CornerGapNodeUniMetric::BlowThisUp();
}

#endif // !_Aft2d_CornerGapNodeUniMetric_Header
