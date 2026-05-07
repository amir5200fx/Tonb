#pragma once
#ifndef _VoyageMesh_NodeBaseFwd_Header
#define _VoyageMesh_NodeBaseFwd_Header

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]

	struct VoyageMesh_NodeTraits;

	template<class NodeTraits>
	class Aft_Node;

	typedef Aft_Node<VoyageMesh_NodeTraits> VoyageMesh_NodeBase;

}

#endif // !_VoyageMesh_NodeBaseFwd_Header
