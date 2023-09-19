#pragma once
#ifndef _MeshPostAF2d_NodeTraits_Header
#define _MeshPostAF2d_NodeTraits_Header

#include <MeshPostAF2d_MetricPrcsrFwd.hxx>
#include <Aft_NodeType.hxx>
#include <Mesh2d_NodeTraits.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations [8/31/2023 aamir]
	class MeshPostAF2d_Element;
	class MeshPostAF2d_Edge;
	class MeshPostAF2d_Node;

	struct MeshPostAF2d_NodeTraits
	{
		typedef MeshPostAF2d_Element elementType;
		typedef MeshPostAF2d_Edge edgeType;
		typedef void facetType;

		static const Aft_NodeType nType = Aft_NodeType_Iso;

		typedef Pnt2d ptType;
		typedef MeshPostAF2d_MetricPrcsr metricPrcsrType;
	};
	
}

#endif // !_MeshPostAF2d_NodeTraits_Header
