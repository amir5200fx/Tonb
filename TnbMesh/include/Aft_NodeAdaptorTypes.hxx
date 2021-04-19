#pragma once
#ifndef _Aft_NodeAdaptorTypes_Header
#define _Aft_NodeAdaptorTypes_Header

#include <Aft_NodeAdaptor.hxx>

#include <Aft_NodesFwd.hxx>
#include <Aft_EdgesFwd.hxx>
#include <Aft_FacetsFwd.hxx>

namespace tnbLib
{

	typedef Mesh_NodeToFrontEdgeAdaptor<Aft2d_Edge> Mesh2d_NodeToFrontEdgeAdaptor;
	typedef Mesh_NodeToFrontEdgeAdaptor<Aft2d_EdgeAnIso> Mesh2d_NodeToFrontEdgeAnIsoAdaptor;
	typedef Mesh_NodeToFrontEdgeAdaptor<Aft2d_EdgeSurface> Mesh2d_NodeToFrontEdgeSurfaceAdaptor;
	typedef Mesh_NodeToFrontEdgeAdaptor<Aft3d_Edge> Mesh3d_NodeToFrontEdgeAdaptor;
	typedef Mesh_NodeToFrontEdgeAdaptor<Aft3d_EdgeAnIso> Mesh3d_NodeToFrontEdgeAnIsoAdaptor;

	typedef Mesh_NodeToFrontFacetAdaptor<Aft3d_Facet> Mesh3d_NodeToFrontFacetAdaptor;
	typedef Mesh_NodeToFrontFacetAdaptor<Aft3d_FacetAnIso> Mesh3d_NodeToFrontFacetAnIsoAdaptor;
}

#endif // !_Aft_NodeAdaptorTypes_Header
