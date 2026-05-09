#pragma once
#ifndef _MeshPostAF2d_EdgeBaseFwd_Header
#define _MeshPostAF2d_EdgeBaseFwd_Header

namespace tnbLib
{

	// Forward Declarations [8/31/2023 aamir]
	struct MeshPostAF2d_EdgeTraits;

	template<class EdgeTraits>
	class Aft_Edge;

	typedef Aft_Edge<MeshPostAF2d_EdgeTraits> MeshPostAF2d_EdgeBase;

}

#endif // !_MeshPostAF2d_EdgeBaseFwd_Header
