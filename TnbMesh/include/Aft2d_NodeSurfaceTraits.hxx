#pragma once
#ifndef _Aft2d_NodeSurfaceTraits_Header
#define _Aft2d_NodeSurfaceTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft2d_ElementSurfaceFwd.hxx>
#include <Aft_NodeType.hxx>
#include <Mesh2d_NodeTraits.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>

namespace tnbLib
{

	struct Aft2d_NodeSurfaceTraits
	{
		typedef Aft2d_EdgeSurface edgeType;
		typedef Aft2d_ElementSurface elementType;
		typedef void facetType;

		static const Aft_NodeType nType = Aft_NodeType_Surface;

		typedef Pnt2d ptType;
		typedef Geo2d_MetricPrcsrAnIso metricPrcsrType;
	};
}

#endif // !_Aft2d_NodeSurfaceTraits_Header