#pragma once
#ifndef _Aft2d_BoundaryOfPlaneAnIso_Header
#define _Aft2d_BoundaryOfPlaneAnIso_Header

#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft_BoundaryOfPlane.hxx>
#include <Aft2d_RegionPlaneAnIso.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>
#include <Aft2d_PlnWireAnIso.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_BoundaryOfPlaneAnIsoFwd.hxx>

#ifdef _DEBUG
namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Aft2d_BoundaryOfPlaneAnIso::UpdateFront();
}
#endif // _DEBUG

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_BoundaryOfPlaneAnIso::RemoveDegeneracies();

	template<>
	TnbMesh_EXPORT void Aft2d_BoundaryOfPlaneAnIso::Perform();
}

#endif // !_Aft2d_BoundaryOfPlaneAnIso_Header
