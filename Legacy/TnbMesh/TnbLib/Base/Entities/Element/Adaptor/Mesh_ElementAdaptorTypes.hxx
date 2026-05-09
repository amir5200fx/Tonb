#pragma once
#ifndef _Mesh_ElementAdaptorTypes_Header
#define _Mesh_ElementAdaptorTypes_Header

#include <Mesh_ElementAdaptor.hxx>

#include <Mesh3d_ElementFwd.hxx>
#include <Mesh3d_FacetFwd.hxx>
#include <Mesh2d_ElementFwd.hxx>

namespace tnbLib
{

	typedef Mesh_ElementAdaptor<Mesh3d_Element, Mesh_ElementType_Tetrahedron> Mesh3d_ElementAdaptor;
	typedef Mesh_ElementAdaptor<Mesh2d_Element, Mesh_ElementType_Triangle2D> Mesh2d_ElementAdaptor;
	typedef Mesh_ElementAdaptor<Mesh3d_Element, Mesh_ElementType_Triangle3D> Mesh3d_FacetElementAdaptor;
}

#endif // !_Mesh_ElementAdaptorTypes_Header
