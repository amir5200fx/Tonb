#pragma once
#ifndef _Geo2d_KnitChain_Header
#define _Geo2d_KnitChain_Header

#include <Geo2d_KnitChainTraits.hxx>
#include <Geo_KnitChain.hxx>
#include <Geo2d_KnitChainFwd.hxx>
#include <Geo2d_GraphNode.hxx>
#include <Geo2d_GraphEdge.hxx>
#include <Entity2d_Chain.hxx>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT void Geo2d_KnitChain::Perform();
}

#endif // !_Geo2d_KnitChain_Header
