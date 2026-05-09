#pragma once
#ifndef _MeshPostAF2d_Traits_Header
#define _MeshPostAF2d_Traits_Header

#include <MeshPostAF2d_ElementBaseFwd.hxx>
#include <MeshPostAF2d_EdgeBaseFwd.hxx>
#include <MeshPostAF2d_NodeBaseFwd.hxx>
#include <Mesh_TypeTraits.hxx>
#include <Aft_OptNode_AnalyticalTraits.hxx>
#include <Aft_OptNodeAnIso_Traits.hxx>

namespace tnbLib
{

	// Forward Declarations [8/31/2023 aamir]
	class MeshPostAF2d_Element;
	class MeshPostAF2d_Edge;
	class MeshPostAF2d_Node;

	template<> struct sub_type<MeshPostAF2d_Element, 0> { typedef MeshPostAF2d_Node type; };
	template<> struct sub_type<MeshPostAF2d_Element, 1> { typedef MeshPostAF2d_Edge type; };
	template<> struct sub_type<MeshPostAF2d_Element, 2> { typedef MeshPostAF2d_Element type; };

	template<> struct sub_type<MeshPostAF2d_Edge, 0> { typedef MeshPostAF2d_Node type; };
	template<> struct sub_type<MeshPostAF2d_Edge, 1> { typedef MeshPostAF2d_Edge type; };

	template<> struct sub_type<MeshPostAF2d_Node, 0> { typedef MeshPostAF2d_Node type; };

	template<> struct sub_type<MeshPostAF2d_ElementBase, 0> { typedef MeshPostAF2d_Node type; };
	template<> struct sub_type<MeshPostAF2d_ElementBase, 1> { typedef MeshPostAF2d_Edge type; };
	template<> struct sub_type<MeshPostAF2d_ElementBase, 2> { typedef MeshPostAF2d_Element type; };

	template<> struct point_type_from_front<MeshPostAF2d_Edge> { typedef Pnt2d ptType; };
	
}

#endif // !_MeshPostAF2d_Traits_Header
