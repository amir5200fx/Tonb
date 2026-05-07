#pragma once
#ifndef _MeshPostAF2d_ElementTraits_Header
#define _MeshPostAF2d_ElementTraits_Header

#include <Entity_Connectivity.hxx>

namespace tnbLib
{

	// Forward Declarations [8/31/2023 aamir]
	class MeshPostAF2d_Element;
	class MeshPostAF2d_Edge;
	class MeshPostAF2d_Node;

	struct MeshPostAF2d_ElementTraits
	{
		typedef MeshPostAF2d_Element elementType;
		typedef void facetType;
		typedef MeshPostAF2d_Edge edgeType;
		typedef MeshPostAF2d_Node nodeType;

		typedef connectivity::triple connectType;
	};

}

#endif // !_MeshPostAF2d_ElementTraits_Header
