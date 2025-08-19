#pragma once
#ifndef _Aft3d_BndNodeFwd_Header
#define _Aft3d_BndNodeFwd_Header

namespace tnbLib
{

	// Forward Declarations
	template<class BndNodeTraits>
	class Mesh_BndNode;

	struct Aft3d_BndNodeTraits;

	typedef Mesh_BndNode<Aft3d_BndNodeTraits>
		Aft3d_BndNode;
}

#endif // !_Aft3d_BndNodeFwd_Header