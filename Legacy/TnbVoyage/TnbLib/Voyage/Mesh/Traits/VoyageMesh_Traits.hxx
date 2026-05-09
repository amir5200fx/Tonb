#pragma once
#ifndef _VoyageMesh_Traits_Header
#define _VoyageMesh_Traits_Header

#include <VoyageMesh_ElementBaseFwd.hxx>
#include <VoyageMesh_EdgeBaseFwd.hxx>
#include <VoyageMesh_NodeBaseFwd.hxx>
#include <Mesh_TypeTraits.hxx>
#include <Aft_OptNode_AnalyticalTraits.hxx>
#include <Aft_OptNodeAnIso_Traits.hxx>

#include <VoyageMesh_OptNode_StandardFwd.hxx>
#include <VoyageMesh_OptNode_AltrFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [8/13/2023 aamir]
	class VoyageMesh_Element;
	class VoyageMesh_Edge;
	class VoyageMesh_Node;

	template<> struct sub_type<VoyageMesh_Element, 0> { typedef VoyageMesh_Node type; };
	template<> struct sub_type<VoyageMesh_Element, 1> { typedef VoyageMesh_Edge type; };
	template<> struct sub_type<VoyageMesh_Element, 2> { typedef VoyageMesh_Element type; };

	template<> struct sub_type<VoyageMesh_Edge, 0> { typedef VoyageMesh_Node type; };
	template<> struct sub_type<VoyageMesh_Edge, 1> { typedef VoyageMesh_Edge type; };

	template<> struct sub_type<VoyageMesh_Node, 0> { typedef VoyageMesh_Node type; };

	template<> struct sub_type<VoyageMesh_ElementBase, 0> { typedef VoyageMesh_Node type; };
	template<> struct sub_type<VoyageMesh_ElementBase, 1> { typedef VoyageMesh_Edge type; };
	template<> struct sub_type<VoyageMesh_ElementBase, 2> { typedef VoyageMesh_Element type; };

	template<> struct point_type_from_front<VoyageMesh_Edge> { typedef Pnt2d ptType; };

	template<> struct info_type_from_aniso_optNode_alg<VoyageMesh_OptNode_Standard> { typedef Aft_SizeCorr_IterativeInfo infoType; };
	template<> struct info_type_from_aniso_optNode_alg<VoyageMesh_OptNode_Altr> { typedef Aft_SizeCorr_IterativeInfo infoType; };
}

#endif // !_VoyageMesh_Traits_Header
