#pragma once
#ifndef _Geo_ApprxCurve_Traits_Header
#define _Geo_ApprxCurve_Traits_Header

#include <Geo_ApprxCurve_Info.hxx>
#include <Geo_Traits.hxx>

#include <gp_Pnt2d.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec2d.hxx>
#include <gp_Vec.hxx>

#include <memory>

class Geom2d_Curve;
class Geom_Curve;

namespace tnbLib
{

	template<class CurveType>
	struct Geo_ApprxCurve_Traits
	{};

	template<>
	struct Geo_ApprxCurve_Traits<Geom2d_Curve>
	{
		typedef gp_Pnt2d ptType;
		typedef gp_Vec2d vtType;
	};

	template<>
	struct Geo_ApprxCurve_Traits<Geom_Curve>
	{
		typedef gp_Pnt ptType;
		typedef gp_Vec vtType;
	};


	template<class CurveType>
	struct Geo_ApprxCurveInfo_Traits
	{
		typedef Geo_ApprxCurve_Info infoType;
	};
}

#endif // !_Geo_ApprxCurve_Traits_Header
