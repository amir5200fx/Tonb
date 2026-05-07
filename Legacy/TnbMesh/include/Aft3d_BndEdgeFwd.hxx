#pragma once
#ifndef _Aft3d_BndEdgeFwd_Header
#define _Aft3d_BndEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations
	template<class BndEdgeTraits>
	class Mesh_BndEdge;

	struct Aft3d_BndEdgeTraits;

	typedef Mesh_BndEdge<Aft3d_BndEdgeTraits>
		Aft3d_BndEdge;
}

#endif // !_Aft3d_BndEdgeFwd_Header