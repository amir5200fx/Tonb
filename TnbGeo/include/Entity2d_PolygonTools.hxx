#pragma once
#ifndef _Entity2d_PolygonTools_Header
#define _Entity2d_PolygonTools_Header

#include <Geo_Module.hxx>
#include <Entity2d_PolygonSide.hxx>
#include <Entity2d_PolygonOrientation.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_TriangleFwd.hxx>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

namespace tnbLib
{

	class Entity2d_PolygonTools
	{

	public:

		static TnbGeo_EXPORT Entity2d_PolygonOrientation GetOrientation(const Entity2d_Triangle& theTri);

		static TnbGeo_EXPORT Entity2d_PolygonOrientation GetOrientation(const Entity_Triangle<const Pnt2d&>& theTri);

		static TnbGeo_EXPORT Entity2d_PolygonOrientation GetOrientation(const Entity2d_Polygon& thePolygon);

		typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
		typedef K::Point_2 Point;

		static TnbGeo_EXPORT Entity2d_PolygonSide GetSide(const Point& pt, Point* pt_begin, Point* pt_end, K traits = K());

		
	};
}

#endif // !_Entity2d_PolygonTools_Header
