#pragma once
#ifndef _Aft_BoundaryOfPlane_Traits_Header
#define _Aft_BoundaryOfPlane_Traits_Header

#include <Aft2d_RegionPlaneFwd.hxx>
#include <Aft2d_RegionPlaneAnIsoFwd.hxx>
#include <Aft2d_gRegionPlaneSurfaceFwd.hxx>
#include <Aft2d_tRegionPlaneSurfaceFwd.hxx>
#include <Aft2d_BoundaryOfPlane_InfoFwd.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_InfoFwd.hxx>

#include <Aft2d_SegmentEdgeFwd.hxx>
#include <Aft2d_SegmentEdgeAnIsoFwd.hxx>
#include <Aft2d_gSegmentEdgeFwd.hxx>
#include <Aft2d_tSegmentEdgeFwd.hxx>

namespace tnbLib
{

	template<class RegionType> struct aft_boundary_of_plane_info_type {};

	template<> struct aft_boundary_of_plane_info_type<Aft2d_RegionPlane> { typedef Aft2d_BoundaryOfPlane_Info type; };
	template<> struct aft_boundary_of_plane_info_type<Aft2d_RegionPlaneAnIso> { typedef Aft2d_BoundaryOfPlaneAnIso_Info type; };
	template<> struct aft_boundary_of_plane_info_type<Aft2d_gRegionPlaneSurface> { typedef Aft2d_BoundaryOfPlaneAnIso_Info type; };
	template<> struct aft_boundary_of_plane_info_type<Aft2d_tRegionPlaneSurface> { typedef Aft2d_BoundaryOfPlaneAnIso_Info type; };

	template<class RegionType> struct aft_boundary_of_plane_entity_type {};

	template<> struct aft_boundary_of_plane_entity_type<Aft2d_RegionPlane> { typedef Aft2d_SegmentEdge type; };
	template<> struct aft_boundary_of_plane_entity_type<Aft2d_RegionPlaneAnIso> { typedef Aft2d_SegmentEdgeAnIso type; };
	template<> struct aft_boundary_of_plane_entity_type<Aft2d_gRegionPlaneSurface> { typedef Aft2d_gSegmentEdge type; };
	template<> struct aft_boundary_of_plane_entity_type<Aft2d_tRegionPlaneSurface> { typedef Aft2d_tSegmentEdge type; };
}

#endif // !_Aft_BoundaryOfPlane_Traits_Header
