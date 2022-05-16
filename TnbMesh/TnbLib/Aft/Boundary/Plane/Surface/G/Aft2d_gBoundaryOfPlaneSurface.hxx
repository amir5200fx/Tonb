#pragma once
#ifndef _Aft2d_gBoundaryOfPlaneSurface_Header
#define _Aft2d_gBoundaryOfPlaneSurface_Header

#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft_BoundaryOfPlane.hxx>
#ifndef _DEBUG
#include <Aft2d_gPlnCurveSurface.hxx>
#include <Cad_gSingularCurve.hxx>
#include <Cad_gPlnGapCurve.hxx>
#include <Aft2d_gSegmentGapEdge.hxx>
#endif // !_DEBUG
#include <Aft2d_gRegionPlaneSurface.hxx>
#include <Aft2d_gSegmentEdge.hxx>
#include <Aft2d_gPlnWireSurface.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_gBoundaryOfPlaneSurfaceFwd.hxx>
#include <Mesh_Module.hxx>

#ifdef _DEBUG
namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_gBoundaryOfPlaneSurface::RemoveDegeneracies();

	template<>
	TnbMesh_EXPORT void Aft2d_gBoundaryOfPlaneSurface::UpdateFront();

	template<>
	TnbMesh_EXPORT void Aft2d_gBoundaryOfPlaneSurface::Perform();
}
#endif // _DEBUG


#endif // !_Aft2d_gBoundaryOfPlaneSurface_Header
