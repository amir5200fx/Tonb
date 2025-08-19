#pragma once
#ifndef _Aft_OptNode_AnalyticalTraits_Header
#define _Aft_OptNode_AnalyticalTraits_Header

#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft3d_EdgeFwd.hxx>

namespace tnbLib
{
	// Forward Declarations [3/5/2022 Amir]

	class Pnt2d;
	class Pnt3d;

	template<class FrontType>
	struct point_type_from_front{};

	template<> struct point_type_from_front<Aft2d_Edge> { typedef Pnt2d ptType; };
	template<> struct point_type_from_front<Aft2d_EdgeAnIso> { typedef Pnt2d ptType; };
	template<> struct point_type_from_front<Aft2d_EdgeSurface> { typedef Pnt2d ptType; };

	template<> struct point_type_from_front<Aft3d_Edge> { typedef Pnt3d ptType; };
}

#endif // !_Aft_OptNode_AnalyticalTraits_Header
