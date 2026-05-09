#pragma once
#ifndef _Aft2d_BndEdgeAnIsoFwd_Header
#define _Aft2d_BndEdgeAnIsoFwd_Header

namespace tnbLib
{
	// Forward Declarations
	template<class BndEdgeTraits>
	class Mesh_BndEdge;

	struct Aft2d_BndEdgeAnIsoTraits;

	typedef Mesh_BndEdge<Aft2d_BndEdgeAnIsoTraits>
		Aft2d_BndEdgeAnIso;
}

#endif // !_Aft2d_BndEdgeAnIsoFwd_Header