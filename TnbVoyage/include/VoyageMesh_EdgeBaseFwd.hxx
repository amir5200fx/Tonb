#pragma once
#ifndef _VoyageMesh_EdgeBaseFwd_Header
#define _VoyageMesh_EdgeBaseFwd_Header

namespace tnbLib
{

	// Forward Declarations

	struct VoyageMesh_EdgeTraits;

	template<class EdgeTraits>
	class Aft_Edge;

	typedef Aft_Edge<VoyageMesh_EdgeTraits> VoyageMesh_EdgeBase;
}

#endif // !_VoyageMesh_EdgeBaseFwd_Header
