#pragma once
#ifndef _VoyageMesh_NodeTraits_Header
#define _VoyageMesh_NodeTraits_Header

#include <VoyageMesh_MetricPrcsrFwd.hxx>
#include <Aft_NodeType.hxx>
#include <Mesh2d_NodeTraits.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	
	class VoyageMesh_Element;
	class VoyageMesh_Edge;
	class VoyageMesh_Node;

	struct VoyageMesh_NodeTraits
	{
		typedef VoyageMesh_Edge edgeType;
		typedef VoyageMesh_Element elementType;
		typedef void facetType;

		static const Aft_NodeType nType = Aft_NodeType_Surface;

		typedef Pnt2d ptType;
		typedef VoyageMesh_MetricPrcsr metricPrcsrType;
	};

}

#endif // !_VoyageMesh_NodeTraits_Header
