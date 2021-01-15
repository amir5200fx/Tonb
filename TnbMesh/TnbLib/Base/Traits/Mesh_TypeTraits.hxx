#pragma once
#ifndef _Mesh_TypeTraits_Header
#define _Mesh_TypeTraits_Header

#include <Traits.hxx>
#include <Mesh2d_NodeFwd.hxx>
#include <Mesh2d_EdgeFwd.hxx>
#include <Mesh2d_ElementFwd.hxx>
#include <Mesh3d_NodeFwd.hxx>
#include <Mesh3d_EdgeFwd.hxx>
#include <Mesh3d_FacetFwd.hxx>
#include <Mesh3d_ElementFwd.hxx>

#include <Aft_NodesFwd.hxx>
#include <Aft_EdgesFwd.hxx>
#include <Aft_FacetsFwd.hxx>
#include <Aft_ElementsFwd.hxx>

#include <Mesh_FacetFwd.hxx>

namespace tnbLib
{

	template<class T, int Rank> struct sub_type {};

	template<> struct sub_type<Mesh2d_Element, 0> { typedef Mesh2d_Node type; };
	template<> struct sub_type<Mesh2d_Element, 1> { typedef Mesh2d_Edge type; };
	template<> struct sub_type<Mesh2d_Element, 2> { typedef Mesh2d_Element type; };

	template<> struct sub_type<Mesh3d_Element, 0> { typedef Mesh3d_Node type; };
	template<> struct sub_type<Mesh3d_Element, 1> { typedef Mesh3d_Edge type; };
	template<> struct sub_type<Mesh3d_Element, 2> { typedef Mesh3d_Facet type; };
	template<> struct sub_type<Mesh3d_Element, 3> { typedef Mesh3d_Element type; };

	template<> struct sub_type<Mesh3d_Facet, 0> { typedef Mesh3d_Node type; };
	template<> struct sub_type<Mesh3d_Facet, 1> { typedef Mesh3d_Edge type; };
	template<> struct sub_type<Mesh3d_Facet, 2> { typedef Mesh3d_Facet type; };

	template<> struct sub_type<Aft2d_Node, 0> { typedef Aft2d_Node type; };
	template<> struct sub_type<Aft2d_Edge, 0> { typedef Aft2d_Node type; };
	template<> struct sub_type<Aft2d_Edge, 1> { typedef Aft2d_Edge type; };
	template<> struct sub_type<Aft2d_Element, 0> { typedef Aft2d_Node type; };
	template<> struct sub_type<Aft2d_Element, 1> { typedef Aft2d_Edge type; };
	template<> struct sub_type<Aft2d_Element, 2> { typedef Aft2d_Element type; };

	template<> struct sub_type<Aft3d_Facet, 0> { typedef Aft3d_Node type; };
	template<> struct sub_type<Aft3d_Facet, 1> { typedef Aft3d_Edge type; };
	template<> struct sub_type<Aft3d_Facet, 2> { typedef Aft3d_Facet type; };

	template<> struct sub_type<Aft3d_FacetAnIso, 0> { typedef Aft3d_NodeAnIso type; };
	template<> struct sub_type<Aft3d_FacetAnIso, 1> { typedef Aft3d_EdgeAnIso type; };
	template<> struct sub_type<Aft3d_FacetAnIso, 2> { typedef Aft3d_FacetAnIso type; };

	template<> struct sub_type<Aft2d_NodeAnIso, 0> { typedef Aft2d_NodeAnIso type; };
	template<> struct sub_type<Aft2d_EdgeAnIso, 0> { typedef Aft2d_NodeAnIso type; };
	template<> struct sub_type<Aft2d_EdgeAnIso, 1> { typedef Aft2d_EdgeAnIso type; };
	template<> struct sub_type<Aft2d_ElementAnIso, 0> { typedef Aft2d_NodeAnIso type; };
	template<> struct sub_type<Aft2d_ElementAnIso, 1> { typedef Aft2d_EdgeAnIso type; };
	template<> struct sub_type<Aft2d_ElementAnIso, 2> { typedef Aft2d_ElementAnIso type; };

	template<> struct sub_type<Aft2d_NodeSurface, 0> { typedef Aft2d_NodeSurface type; };
	template<> struct sub_type<Aft2d_EdgeSurface, 0> { typedef Aft2d_NodeSurface type; };
	template<> struct sub_type<Aft2d_EdgeSurface, 1> { typedef Aft2d_EdgeSurface type; };
	template<> struct sub_type<Aft2d_ElementSurface, 0> { typedef Aft2d_NodeSurface type; };
	template<> struct sub_type<Aft2d_ElementSurface, 1> { typedef Aft2d_EdgeSurface type; };
	template<> struct sub_type<Aft2d_ElementSurface, 2> { typedef Aft2d_ElementSurface type; };

	template<> struct sub_type<Aft3d_Element, 0> { typedef Aft3d_Node type; };
	template<> struct sub_type<Aft3d_Element, 1> { typedef Aft3d_Edge type; };
	template<> struct sub_type<Aft3d_Element, 2> { typedef Aft3d_Facet type; };
	template<> struct sub_type<Aft3d_Element, 3> { typedef Aft3d_Element type; };

	template<> struct sub_type<Aft3d_ElementAnIso, 0> { typedef Aft3d_NodeAnIso type; };
	template<> struct sub_type<Aft3d_ElementAnIso, 1> { typedef Aft3d_EdgeAnIso type; };
	template<> struct sub_type<Aft3d_ElementAnIso, 2> { typedef Aft3d_FacetAnIso type; };
	template<> struct sub_type<Aft3d_ElementAnIso, 3> { typedef Aft3d_ElementAnIso type; };

}

#endif // !_Mesh_TypeTraits_Header