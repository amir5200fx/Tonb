#pragma once
#ifndef _VoyageMesh_FrontTraits_Header
#define _VoyageMesh_FrontTraits_Header

#include <Aft_FrontTraits.hxx>
#include <Aft_TypeTraits.hxx>

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	class VoyageMesh_Node;
	class VoyageMesh_Edge;
	class VoyageMesh_Element;

	template<>
	struct Aft_FrontTraits<VoyageMesh_Edge>
	{
		typedef VoyageMesh_Node nodeType;
		typedef VoyageMesh_Edge edgeType;
		typedef VoyageMesh_Element elementType;
	};

	template<> struct is_anisoType<VoyageMesh_Node> : std::true_type {};
	template<> struct is_anisoType<VoyageMesh_Edge> : std::true_type {};
	template<> struct is_anisoType<VoyageMesh_Element> : std::true_type {};
}

#endif // !_VoyageMesh_FrontTraits_Header
