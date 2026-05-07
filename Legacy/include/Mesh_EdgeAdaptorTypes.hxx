#pragma once
#ifndef _Mesh_EdgeAdaptorTypes_Header
#define _Mesh_EdgeAdaptorTypes_Header

#include <Mesh_EdgeAdaptor.hxx>

#include <Mesh2d_ElementFwd.hxx>
#include <Mesh3d_FacetFwd.hxx>
#include <Mesh3d_ElementFwd.hxx>

namespace tnbLib
{

	typedef Mesh_EdgeToFacetAdaptor<Mesh3d_Facet> Mesh3d_EdgeToFacetAdaptor;
	typedef Mesh_EdgeToElementAdaptor<Mesh3d_Element> Mesh3d_EdgeToElementAdaptor;

}

#endif // !_Mesh_EdgeAdaptorTypes_Header
