#pragma once
#ifndef _Geo3d_KnitChain_Header
#define _Geo3d_KnitChain_Header

#include <Geo3d_KnitChainTraits.hxx>
#include <Geo_KnitChain.hxx>
#include <Geo3d_KnitChainFwd.hxx>
#include <Geo3d_GraphNode.hxx>
#include <Geo3d_GraphEdge.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_PolygonFwd.hxx>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT void Geo3d_KnitChain::Perform();
}

#endif // !_Geo3d_KnitChain_Header
