#pragma once
#ifndef _Aft2d_gBoundaryOfPlaneSurfaceUniMetric_Header
#define _Aft2d_gBoundaryOfPlaneSurfaceUniMetric_Header

#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Aft_BoundaryOfPlane.hxx>
#ifndef _DEBUG
#include <Aft2d_gPlnCurveSurfaceUniMetric.hxx>
#include <Cad_gSingularCurve.hxx>
#endif // !_DEBUG
#include <Aft2d_gRegionPlaneSurfaceUniMetric.hxx>
#include <Aft2d_gSegmentEdgeUniMetric.hxx>
#include <Aft2d_gPlnWireSurfaceUniMetric.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_gBoundaryOfPlaneSurfaceUniMetricFwd.hxx>

#ifdef _DEBUG
namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_gBoundaryOfPlaneSurfaceUniMetric::UpdateFront();
}
#endif // _DEBUG

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_gBoundaryOfPlaneSurfaceUniMetric::RemoveDegeneracies();

	template<>
	TnbMesh_EXPORT void Aft2d_gBoundaryOfPlaneSurfaceUniMetric::Perform();
}

#endif // !_Aft2d_gBoundaryOfPlaneSurfaceUniMetric_Header
