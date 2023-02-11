#pragma once
#ifndef _Aft2d_BoundaryOfPlaneUniMetric_Header
#define _Aft2d_BoundaryOfPlaneUniMetric_Header

#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Aft_BoundaryOfPlane.hxx>
#include <Aft2d_RegionPlaneUniMetric.hxx>
#include <Aft2d_SegmentEdgeUniMetric.hxx>
#include <Aft2d_PlnWireUniMetric.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_BoundaryOfPlaneUniMetricFwd.hxx>

#ifdef _DEBUG
namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_BoundaryOfPlaneUniMetric::UpdateFront();
}
#endif // _DEBUG


namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_BoundaryOfPlaneUniMetric::RemoveDegeneracies();

	template<>
	TnbMesh_EXPORT void Aft2d_BoundaryOfPlaneUniMetric::Perform();
}

#endif // !_Aft2d_BoundaryOfPlaneUniMetric_Header
