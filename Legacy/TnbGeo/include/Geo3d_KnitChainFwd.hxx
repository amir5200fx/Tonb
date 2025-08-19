#pragma once
#ifndef _Geo3d_KnitChainFwd_Header
#define _Geo3d_KnitChainFwd_Header

namespace tnbLib
{

	// Forward Declarations [2/6/2023 Payvand]
	template<class KnitTraits>
	class Geo_KnitChain;

	struct Geo3d_KnitChainTraits;

	typedef Geo_KnitChain<Geo3d_KnitChainTraits>
		Geo3d_KnitChain;
}

#endif // !_Geo3d_KnitChainFwd_Header
