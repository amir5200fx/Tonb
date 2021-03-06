#pragma once
#ifndef _Aft2d_BndEdgeFwd_Header
#define _Aft2d_BndEdgeFwd_Header

namespace tnbLib
{

	// Forward Declarations
	template<class BndEdgeTraits>
	class Mesh_BndEdge;

	struct Aft2d_BndEdgeTraits;

	typedef Mesh_BndEdge<Aft2d_BndEdgeTraits>
		Aft2d_BndEdge;
}

#endif // !_Aft2d_BndEdgeFwd_Header