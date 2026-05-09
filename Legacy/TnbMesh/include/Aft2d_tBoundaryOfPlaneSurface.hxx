#pragma once
#ifndef _Aft2d_tBoundaryOfPlaneSurface_Header
#define _Aft2d_tBoundaryOfPlaneSurface_Header

#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft_BoundaryOfPlane.hxx>
#ifndef _DEBUG
#include <Aft2d_gPlnCurveSurface.hxx>
#include <Cad_gSingularCurve.hxx>
#include <Cad_gPoleSingularCurve.hxx>
#include <Cad_gLineSingularCurve.hxx>
#include <Cad_gPlnGapCurve.hxx>
#include <Aft2d_gSegmentGapEdge.hxx>
#endif // !_DEBUG
#include <Aft2d_tRegionPlaneSurface.hxx>
#include <Aft2d_tSegmentEdge.hxx>
#include <Aft2d_tPlnWireSurface.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_tBoundaryOfPlaneSurfaceFwd.hxx>

#ifdef _DEBUG
namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_tBoundaryOfPlaneSurface::RemoveDegeneracies();

	template<>
	TnbMesh_EXPORT void Aft2d_tBoundaryOfPlaneSurface::Perform();
}
#endif // _DEBUG

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_tBoundaryOfPlaneSurface::UpdateFront();
}

#endif // !_Aft2d_tBoundaryOfPlaneSurface_Header
