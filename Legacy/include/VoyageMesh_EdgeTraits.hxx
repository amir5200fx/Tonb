#pragma once
#ifndef _VoyageMesh_EdgeTraits_Header
#define _VoyageMesh_EdgeTraits_Header

#include <VoyageMesh_Node.hxx>
#include <Mesh2d_EdgeTraits.hxx>

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	class VoyageMesh_Element;

	struct VoyageMesh_EdgeTraits
	{
		typedef VoyageMesh_Node nodeType;
		typedef void facetType;
		typedef VoyageMesh_Element elementType;

		static constexpr bool geomInfo = true;
	};
}

#endif // !_VoyageMesh_EdgeTraits_Header
