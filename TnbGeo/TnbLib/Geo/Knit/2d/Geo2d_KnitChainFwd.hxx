#pragma once
#ifndef _Geo2d_KnitChainFwd_Header
#define _Geo2d_KnitChainFwd_Header

namespace tnbLib
{

	// Forward Declarations [1/5/2022 Amir]
	template<class KnitTraits>
	class Geo_KnitChain;

	struct Geo2d_KnitChainTraits;

	typedef Geo_KnitChain<Geo2d_KnitChainTraits>
		Geo2d_KnitChain;
}

#endif // !_Geo2d_KnitChainFwd_Header
