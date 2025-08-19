#pragma once
#ifndef _Aft2d_tBoundaryOfPlaneSurfaceUniMetric_Header
#define _Aft2d_tBoundaryOfPlaneSurfaceUniMetric_Header

#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Aft_BoundaryOfPlane.hxx>
#include <Aft2d_tRegionPlaneSurfaceUniMetric.hxx>
#include <Aft2d_tSegmentEdgeUniMetric.hxx>
#include <Aft2d_tPlnWireSurfaceUniMetric.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_tBoundaryOfPlaneSurfaceUniMetricFwd.hxx>

#ifdef _DEBUG
namespace tnbLib
{
	
}
#endif // _DEBUG

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_tBoundaryOfPlaneSurfaceUniMetric::UpdateFront();

	template<>
	TnbMesh_EXPORT void Aft2d_tBoundaryOfPlaneSurfaceUniMetric::RemoveDegeneracies();

	template<>
	TnbMesh_EXPORT void Aft2d_tBoundaryOfPlaneSurfaceUniMetric::Perform();
}

#endif // !_Aft2d_tBoundaryOfPlaneSurfaceUniMetric_Header
