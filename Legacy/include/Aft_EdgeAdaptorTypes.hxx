#pragma once
#ifndef _Aft_EdgeAdaptorTypes_Header
#define _Aft_EdgeAdaptorTypes_Header

#include <Mesh_EdgeAdaptor.hxx>

#include <Aft_NodesFwd.hxx>
#include <Aft_EdgesFwd.hxx>
#include <Aft_FacetsFwd.hxx>
#include <Aft_ElementsFwd.hxx>

namespace tnbLib
{

	typedef Mesh_EdgeToFacetAdaptor<Aft3d_Facet> Aft3d_EdgeToFacetAdaptor;
	typedef Mesh_EdgeToFacetAdaptor<Aft3d_FacetAnIso> Aft3d_EdgeToFacetAnIsoAdaptor;

	typedef Mesh_EdgeToElementAdaptor<Aft3d_Element> Aft3d_EdgeToElementAdaptor;
	typedef Mesh_EdgeToElementAdaptor<Aft3d_ElementAnIso> Aft3d_EdgeToElementAnIsoAdaptor;
}

#endif // !_Aft_EdgeAdaptorTypes_Header
