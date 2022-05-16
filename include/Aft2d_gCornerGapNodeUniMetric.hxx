#pragma once
#ifndef _Aft2d_gCornerGapNodeUniMetric_Header
#define _Aft2d_gCornerGapNodeUniMetric_Header

#include <Aft2d_gCornerGapNodeUniMetricFwd.hxx>
#include <Aft2d_GapNodeTemplate.hxx>
#include <Aft2d_gCornerNodeUniMetric.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_gCornerGapNodeUniMetric::BlowThisUp(const Geo2d_MetricPrcsrUniMetric&);
}

#endif // !_Aft2d_gCornerGapNodeUniMetric_Header
