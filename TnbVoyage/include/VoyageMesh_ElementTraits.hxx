#pragma once
#ifndef _VoyageMesh_ElementTraits_Header
#define _VoyageMesh_ElementTraits_Header

#include <Entity_Connectivity.hxx>

namespace tnbLib
{

	// Forward Declarations [8/13/2023 aamir]
	class VoyageMesh_Element;
	class VoyageMesh_Edge;
	class VoyageMesh_Node;

	struct VoyageMesh_ElementTraits
	{
		typedef VoyageMesh_Node nodeType;
		typedef VoyageMesh_Edge edgeType;
		typedef void facetType;
		typedef VoyageMesh_Element elementType;

		typedef connectivity::triple connectType;
	};
}

#endif // !_VoyageMesh_ElementTraits_Header
