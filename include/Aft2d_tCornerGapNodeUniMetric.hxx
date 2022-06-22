#pragma once
#ifndef _Aft2d_tCornerGapNodeUniMetric_Header
#define _Aft2d_tCornerGapNodeUniMetric_Header

#include <Aft2d_tCornerGapNodeUniMetricFwd.hxx>
#include <Aft2d_GapNodeTemplate.hxx>
#include <Aft2d_tCornerNodeUniMetric.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::shared_ptr<Aft2d_BndEdgeSurface>
		Aft2d_tCornerGapNodeUniMetric::BlowThisUp();
}

#endif // !_Aft2d_tCornerGapNodeUniMetric_Header
