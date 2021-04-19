#pragma once
#ifndef _Mesh_NodeAdaptorTypes_Header
#define _Mesh_NodeAdaptorTypes_Header

#include <Mesh_NodeAdaptor.hxx>

#include <Mesh2d_NodeFwd.hxx>
#include <Mesh2d_EdgeFwd.hxx>
#include <Mesh2d_ElementFwd.hxx>
#include <Mesh3d_NodeFwd.hxx>
#include <Mesh3d_EdgeFwd.hxx>
#include <Mesh3d_FacetFwd.hxx>
#include <Mesh3d_ElementFwd.hxx>

namespace tnbLib
{

	typedef Mesh_NodeToEdgeAdaptor<Mesh3d_Edge> Mesh3d_NodeToEdgeAdaptor;
	typedef Mesh_NodeToFacetAdaptor<Mesh3d_Facet> Mesh3d_NodeToFacetAdaptor;
	typedef Mesh_NodeToElementAdaptor<Mesh3d_Element> Mesh3d_NodeToElementAdaptor;

	typedef Mesh_NodeToBoundaryEdgeAdaptor<Mesh3d_Edge> Mesh3d_NodeToBoundaryEdgeAdaptor;
	typedef Mesh_NodeToBoundaryFacetAdaptor<Mesh3d_Facet> Mesh3d_NodeToBoundaryFacetAdaptor;

	typedef Mesh_NodeToEdgeAdaptor<Mesh2d_Edge> Mesh2d_NodeToEdgeAdaptor;
	typedef Mesh_NodeToElementAdaptor<Mesh2d_Element> Mesh2d_NodeToElementAdaptor;

	typedef Mesh_NodeToBoundaryEdgeAdaptor<Mesh2d_Edge> Mesh2d_NodeToBoundaryEdgeAdaptor;
}

#endif // !_Mesh_NodeAdaptorTypes_Header
