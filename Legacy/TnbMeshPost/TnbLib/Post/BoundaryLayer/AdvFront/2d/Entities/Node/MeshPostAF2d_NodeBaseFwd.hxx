#pragma once
#ifndef _MeshPostAF2d_NodeBaseFwd_Header
#define _MeshPostAF2d_NodeBaseFwd_Header

namespace tnbLib
{

	// Forward Declarations [8/31/2023 aamir]
	struct MeshPostAF2d_NodeTraits;

	template<class NodeTraits>
	class Aft_Node;

	typedef Aft_Node<MeshPostAF2d_NodeTraits> MeshPostAF2d_NodeBase;
}

#endif // !_MeshPostAF2d_NodeBaseFwd_Header
