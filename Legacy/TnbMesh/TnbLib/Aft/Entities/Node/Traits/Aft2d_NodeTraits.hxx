#pragma once
#ifndef _Aft2d_NodeTraits_Header
#define _Aft2d_NodeTraits_Header

#include <Pnt2d.hxx>
#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_ElementFwd.hxx>
#include <Aft_NodeType.hxx>
#include <Mesh2d_NodeTraits.hxx>
#include <Geo2d_MetricPrcsrFwd.hxx>

namespace tnbLib
{

	struct Aft2d_NodeTraits
	{
		typedef Aft2d_Edge edgeType;
		typedef Aft2d_Element elementType;
		typedef void facetType;

		static const Aft_NodeType nType = Aft_NodeType_Iso;

		typedef Pnt2d ptType;
		typedef Geo2d_MetricPrcsr metricPrcsrType;
	};
}

#endif // !_Aft2d_NodeTraits_Header