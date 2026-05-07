#pragma once
#ifndef _Aft3d_BndEdgeAnIsoFwd_Header
#define _Aft3d_BndEdgeAnIsoFwd_Header

namespace tnbLib
{
	// Forward Declarations
	template<class BndEdgeTraits>
	class Mesh_BndEdge;

	struct Aft3d_BndEdgeAnIsoTraits;

	typedef Mesh_BndEdge<Aft3d_BndEdgeAnIsoTraits>
		Aft3d_BndEdgeAnIso;
}

#endif // !_Aft3d_BndEdgeAnIsoFwd_Header