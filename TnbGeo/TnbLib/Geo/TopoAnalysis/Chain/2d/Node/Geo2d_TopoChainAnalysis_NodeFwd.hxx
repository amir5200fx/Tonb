#pragma once
#ifndef _Geo2d_TopoChainAnalysis_NodeFwd_Header
#define _Geo2d_TopoChainAnalysis_NodeFwd_Header

#include <Geo2d_GraphNodeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/2/2022 Amir]
	template<class NodeType>
	class Knit_ChainNode;

	typedef Knit_ChainNode<Geo2d_GraphNode> Geo2d_TopoChainAnalysis_Node;
}

#endif // !_Geo2d_TopoChainAnalysis_NodeFwd_Header
