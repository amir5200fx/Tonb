#pragma once
#ifndef _Aft_ElementAdaptorTypes_Header
#define _Aft_ElementAdaptorTypes_Header

#include <Mesh_ElementAdaptor.hxx>

#include <Aft_ElementsFwd.hxx>
#include <Aft_FacetsFwd.hxx>

namespace tnbLib
{

	typedef Mesh_ElementAdaptor<Aft3d_Element, Mesh_ElementType_Tetrahedron> Aft3d_ElementAdaptor;
	typedef Mesh_ElementAdaptor<Aft3d_ElementAnIso, Mesh_ElementType_Tetrahedron> Aft3d_ElementAnIsoAdaptor;

	typedef Mesh_ElementAdaptor<Aft2d_Element, Mesh_ElementType_Triangle2D> Aft2d_ElementAdaptor;
	typedef Mesh_ElementAdaptor<Aft2d_ElementAnIso, Mesh_ElementType_Triangle2D> Aft2d_ElementAnIsoAdaptor;
	typedef Mesh_ElementAdaptor<Aft2d_ElementSurface, Mesh_ElementType_Triangle2D> Aft2d_ElementSurfaceAdaptor;

	typedef Mesh_ElementAdaptor<Aft3d_Facet, Mesh_ElementType_Triangle3D> Aft3d_FacetAdaptor;
	typedef Mesh_ElementAdaptor<Aft3d_FacetAnIso, Mesh_ElementType_Triangle3D> Aft3d_FacetAnIsoAdaptor;
}

#endif // !_Aft_ElementAdaptorTypes_Header
