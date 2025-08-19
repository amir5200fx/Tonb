#pragma once
#ifndef _MeshPostAF2d_EdgeTraits_Header
#define _MeshPostAF2d_EdgeTraits_Header

#include <MeshPostAF2d_Node.hxx>
#include <Mesh2d_EdgeTraits.hxx>

namespace tnbLib
{

	// Forward Declarations [8/31/2023 aamir]
	class MeshPostAF2d_Element;

	struct MeshPostAF2d_EdgeTraits
	{
		typedef MeshPostAF2d_Element elementType;
		typedef void facetType;
		typedef MeshPostAF2d_Node nodeType;

		static constexpr bool geomInfo = true;
	};

}

#endif // !_MeshPostAF2d_EdgeTraits_Header
