#pragma once
#ifndef _Aft3d_BndNodeAnIsoFwd_Header
#define _Aft3d_BndNodeAnIsoFwd_Header

namespace tnbLib
{

	// Forward Declaration
	template<class BndNodeTraits>
	class Mesh_BndNode;

	struct Aft3d_BndNodeAnIsoTraits;

	typedef Mesh_BndNode<Aft3d_BndNodeAnIsoTraits>
		Aft3d_BndNodeAnIso;
}

#endif // !_Aft3d_BndNodeAnIsoFwd_Header