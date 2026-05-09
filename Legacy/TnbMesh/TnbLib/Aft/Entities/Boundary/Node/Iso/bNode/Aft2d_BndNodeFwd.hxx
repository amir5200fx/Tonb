#pragma once
#ifndef _Aft2d_BndNodeFwd_Header
#define _Aft2d_BndNodeFwd_Header

namespace tnbLib
{

	// Forward Declarations
	template<class BndNodeTraits>
	class Mesh_BndNode;

	struct Aft2d_BndNodeTraits;

	typedef Mesh_BndNode<Aft2d_BndNodeTraits>
		Aft2d_BndNode;
}

#endif // !_Aft2d_BndNodeFwd_Header