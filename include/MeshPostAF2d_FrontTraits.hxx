#pragma once
#ifndef _MeshPostAF2d_FrontTraits_Header
#define _MeshPostAF2d_FrontTraits_Header

#include <Aft_FrontTraits.hxx>
#include <Aft_TypeTraits.hxx>

namespace tnbLib
{

	// Forward Declarations [9/1/2023 aamir]
	class MeshPostAF2d_Element;
	class MeshPostAF2d_Edge;
	class MeshPostAF2d_Node;

	template<>
	struct Aft_FrontTraits<MeshPostAF2d_Edge>
	{
		typedef MeshPostAF2d_Element elementType;
		typedef MeshPostAF2d_Edge edgeType;
		typedef MeshPostAF2d_Node nodeType;
	};

	template<> struct is_isoType<MeshPostAF2d_Element> : std::true_type {};
	template<> struct is_isoType<MeshPostAF2d_Edge> : std::true_type {};
	template<> struct is_isoType<MeshPostAF2d_Node> : std::true_type {};

}

#endif // !_MeshPostAF2d_FrontTraits_Header
