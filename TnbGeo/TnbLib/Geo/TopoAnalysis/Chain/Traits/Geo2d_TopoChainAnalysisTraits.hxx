#pragma once
#ifndef _Geo2d_TopoChainAnalysisTraits_Header
#define _Geo2d_TopoChainAnalysisTraits_Header

#include <Geo2d_TopoChainAnalysis_NodeFwd.hxx>
#include <Geo2d_GraphEdgeFwd.hxx>
#include <Geo2d_RingGraphEdgeFwd.hxx>
#include <Geo2d_SegmentGraphEdgeFwd.hxx>

namespace tnbLib
{

	struct Geo2d_TopoChainAnalysisTraits
	{
		typedef Geo2d_TopoChainAnalysis_Node nodeType;
		typedef Geo2d_SegmentGraphEdge edgeType;
	};
}

#endif // !_Geo2d_TopoChainAnalysisTraits_Header
