#pragma once
#ifndef _Aft2d_gCornerGapNodeUniMetric_Header
#define _Aft2d_gCornerGapNodeUniMetric_Header

#include <Aft2d_gCornerGapNodeUniMetricFwd.hxx>
#include <Aft2d_GapNodeTemplate.hxx>
#include <Aft2d_gCornerNodeUniMetric.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::shared_ptr<Aft2d_BndEdgeSurface> 
		Aft2d_gCornerGapNodeUniMetric::BlowThisUp();
}

#endif // !_Aft2d_gCornerGapNodeUniMetric_Header
