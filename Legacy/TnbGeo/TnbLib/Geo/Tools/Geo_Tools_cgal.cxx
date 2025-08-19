#include <Geo_Tools.hxx>

#include <Geo2d_CGALPolygonCache.hxx>
#include <Entity2d_Ray.hxx>
#include <Entity2d_Triangle.hxx>
#ifdef Handle
#undef Handle
#endif // Handle
#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\Segment_2.h>
#include <CGAL\Segment_3.h>
#include <CGAL\Polygon_2.h>
#include <CGAL\Plane_3.h>
#include <CGAL\Triangle_3.h>
#include <CGAL\Ray_2.h>
#include <CGAL\intersections.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
static Kernel cgal_object;

typedef Kernel::Segment_2 Segment_2;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Vector_2 Vector_2;
typedef Kernel::Line_2 Line_2;
typedef Kernel::Direction_2 Direction_2;
typedef Kernel::Triangle_2 Triangle_2;
typedef Kernel::Plane_3 Plane_3;
typedef Kernel::Ray_2 Ray_2;

typedef Kernel::Segment_3 Segment_3;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector_3;
typedef Kernel::Triangle_3 Triangle_3;
typedef Kernel::Intersect_2 Intersect_2;
typedef Kernel::Intersect_3 Intersect_3;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
//CGAL_HEADER_ONLY

namespace tnbLib
{
	// Some helper functions
	namespace
	{
		Point_2 get_cgal_point(const Pnt2d& p)
		{
			return { p.X(), p.Y() };
		}

		Point_3 get_cgal_point(const Pnt3d& p)
		{
			return { p.X(), p.Y(), p.Z() };
		}

		Segment_2 get_cgal_segment(const Entity2d_Segment& s)
		{
			return { get_cgal_point(s.P0()), get_cgal_point(s.P1()) };
		}

		/*Segment_3 get_cgal_segment(const Entity3d_Segment& s)
		{
			return { get_cgal_point(s.P0()), get_cgal_point(s.P1()) };
		}*/

		Segment_3 get_cgal_segment(const Entity3d_SegmentRef& s)
		{
			return { get_cgal_point(s.P0()), get_cgal_point(s.P1()) };
		}

		Pnt2d get_point(const Point_2& p)
		{
			return { p.x(), p.y() };
		}

		/*Pnt3d get_point(const Point_3& p)
		{
			return { p.x(), p.y(), p.z() };
		}*/

		Direction_2 get_cgal_direction(const Dir2d& d)
		{
			return { d.X(), d.Y() };
		}

		Dir2d get_dir(const Direction_2& d)
		{
			return { d.dx(), d.dy() };
		}

		Line_2 get_cgal_line(const Entity2d_Line& l)
		{
			return { get_cgal_point(l.P()), get_cgal_direction(l.Dir()) };
		}

		Line_2 get_cgal_line(const Entity2d_LineRef& l)
		{
			return { get_cgal_point(l.P()), get_cgal_direction(l.Dir()) };
		}

		Ray_2 get_cgal_ray(const Entity2d_Ray& r)
		{
			return { get_cgal_point(r.Coord()), get_cgal_direction(r.Direction()) };
		}

		Triangle_2 get_cgal_triangle(const Entity2d_Triangle& t)
		{
			return { get_cgal_point(t.P0()), get_cgal_point(t.P1()), get_cgal_point(t.P2()) };
		}

		Triangle_3 get_cgal_triangle(const Entity3d_Triangle& t)
		{
			return { get_cgal_point(t.P0()), get_cgal_point(t.P1()), get_cgal_point(t.P2()) };
		}
	}
}

Standard_Real
tnbLib::Geo_Tools::Area_cgal(const std::vector<Pnt2d>& thePolygon)
{
	Polygon_2 poly;
	for (const auto& x:thePolygon)
	{
		poly.push_back(Point_2(x.X(), x.Y()));
	}
	return poly.area();
}

Standard_Real 
tnbLib::Geo_Tools::CalcSquareDistancePointFromTriangle_cgal
(
	const Pnt3d& thePoint,
	const Pnt3d& theP0,
	const Pnt3d& theP1,
	const Pnt3d& theP2
)
{
	const auto pt = get_cgal_point(thePoint);
	const Triangle_3 tri(get_cgal_point(theP0), get_cgal_point(theP1), get_cgal_point(theP2));

	return cgal_object.compute_squared_distance_2_object()(pt, tri);
}

Standard_Real 
tnbLib::Geo_Tools::SquareDistance_cgal
(
	const Pnt2d & theQ,
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	const Point_2 Q(theQ.X(), theQ.Y());
	const Segment_2 S(Point_2(theP0.X(), theP0.Y()), Point_2(theP1.X(), theP1.Y()));

	return cgal_object.compute_squared_distance_2_object()(Q, S);
}

Standard_Real 
tnbLib::Geo_Tools::SquareDistance_cgal
(
	const Pnt3d & theQ,
	const Pnt3d & theP0, 
	const Pnt3d & theP1
)
{
	const Point_3 Q(theQ.X(), theQ.Y(), theQ.Z());
	const Segment_3 S(Point_3(theP0.X(), theP0.Y(), theP0.Z()), Point_3(theP1.X(), theP1.Y(), theP1.Z()));

	return cgal_object.compute_squared_distance_3_object()(Q, S);
}

Standard_Real 
tnbLib::Geo_Tools::SquareDistance_cgal
(
	const Pnt3d & theQ,
	const Pnt3d & theP0, 
	const Pnt3d & theP1,
	const Pnt3d & theP2
)
{
	const Point_3 Q(theQ.X(), theQ.Y(), theQ.Z());

	const Triangle_3 S(Point_3(theP0.X(), theP0.Y(), theP0.Z()),
		Point_3(theP1.X(), theP1.Y(), theP1.Z()),
		Point_3(theP2.X(), theP2.Y(), theP2.Z()));

	return cgal_object.compute_squared_distance_3_object()(Q, S);
}

Standard_Real 
tnbLib::Geo_Tools::SquareDistanceSegments_cgal
(
	const Pnt3d & theQ0, 
	const Pnt3d & theQ1, 
	const Pnt3d & theP0, 
	const Pnt3d & theP1
)
{
	const Segment_3 S0(Point_3(theQ0.X(), theQ0.Y(), theQ0.Z()), Point_3(theQ1.X(), theQ1.Y(), theQ1.Z()));
	const Segment_3 S1(Point_3(theP0.X(), theP0.Y(), theP0.Z()), Point_3(theP1.X(), theP1.Y(), theP1.Z()));

	return cgal_object.compute_squared_distance_3_object()(S0, S1);
}

Standard_Real 
tnbLib::Geo_Tools::SquareDistance_cgal
(
	const Pnt3d & thePoint,
	const gp_Pln & thePlane
)
{
	auto[a, b, c, d] = GetCoefficients(thePlane);
	const Plane_3 pln(a, b, c, d);
	const Point_3 pt(thePoint.X(), thePoint.Y(), thePoint.Z());

	return cgal_object.compute_squared_distance_3_object()(pt, pln);
}

Standard_Real 
tnbLib::Geo_Tools::Oriented_cgal
(
	const Pnt2d & theQ, 
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	const Vector_2 dv0(theP0.X() - theQ.X(), theP0.Y() - theQ.Y());
	const Vector_2 dv1(theP1.X() - theQ.X(), theP1.Y() - theQ.Y());

	return cgal_object.compute_determinant_2_object()(dv0, dv1);
}

Standard_Real 
tnbLib::Geo_Tools::Oriented_cgal
(
	const Pnt3d & theQ, 
	const Pnt3d & theP0,
	const Pnt3d & theP1,
	const Pnt3d & theP2
)
{
	/*Vector_3 ad(theP2.X() - theQ.X(), theP2.Y() - theQ.Y(), theP2.Z() - theQ.Z());
	Vector_3 bd(theP2.X() - theP0.X(), theP2.Y() - theP0.Y(), theP2.Z() - theP0.Z());
	Vector_3 cd(theP2.X() - theP1.X(), theP2.Y() - theP1.Y(), theP2.Z() - theP1.Z());*/

	const Vector_3 ad(theQ.X() - theP0.X(), theQ.Y() - theP0.Y(), theQ.Z() - theP0.Z());
	const Vector_3 bd(theQ.X() - theP1.X(), theQ.Y() - theP1.Y(), theQ.Z() - theP1.Z());
	const Vector_3 cd(theQ.X() - theP2.X(), theQ.Y() - theP2.Y(), theQ.Z() - theP2.Z());

	return cgal_object.compute_determinant_3_object()(ad, bd, cd);
}

Standard_Boolean 
tnbLib::Geo_Tools::IsPointInsidePolygon
(
	const Pnt2d& theCoord, 
	const Geo2d_CGALPolygonCache& thePolygon
)
{
	const auto& poly = thePolygon.Polygon();
	const CGAL::Bounded_side side = CGAL::bounded_side_2(poly.begin(), poly.end(), get_cgal_point(theCoord));
	if (side == CGAL::ON_BOUNDED_SIDE) 
	{
		return Standard_True;
	}
	if (side == CGAL::ON_BOUNDARY) 
	{
		// Point is on the boundary of the polygon.;
		return Standard_False;
	}
	// Point is outside the polygon;
	return Standard_False;
	//return thePolygon.Polygon().oriented_side(get_cgalPoint(theCoord)) IS_EQUAL CGAL::ON_POSITIVE_SIDE;
}

Standard_Boolean 
tnbLib::Geo_Tools::HasIntersection_cgal
(
	const Pnt2d & theQ0,
	const Pnt2d & theQ1, 
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	const Segment_2 S1(Point_2(theQ0.X(), theQ0.Y()), Point_2(theQ1.X(), theQ1.Y()));
	const Segment_2 S2(Point_2(theP0.X(), theP0.Y()), Point_2(theP1.X(), theP1.Y()));

	return cgal_object.do_intersect_2_object()(S1, S2);
}

Standard_Boolean 
tnbLib::Geo_Tools::IsIntersectionSegmentTriangle_cgal
(
	const Pnt3d& theP0,
	const Pnt3d& theP1,
	const Pnt3d& theQ0,
	const Pnt3d& theQ1,
	const Pnt3d& theQ2
)
{
	const Segment_3 seg(get_cgal_point(theP0), get_cgal_point(theP1));
	const Triangle_3 tri(get_cgal_point(theQ0), get_cgal_point(theQ1), get_cgal_point(theQ2));

	return cgal_object.do_intersect_3_object()(seg, tri);
}

Standard_Boolean 
tnbLib::Geo_Tools::IsIntersectionTwoTriangles_cgal
(
	const Pnt3d& theP0, 
	const Pnt3d& theP1,
	const Pnt3d& theP2, 
	const Pnt3d& theQ0, 
	const Pnt3d& theQ1,
	const Pnt3d& theQ2
)
{
	const Triangle_3 tri0(get_cgal_point(theP0), get_cgal_point(theP1), get_cgal_point(theP2));
	const Triangle_3 tri1(get_cgal_point(theQ0), get_cgal_point(theQ1), get_cgal_point(theQ2));

	return cgal_object.do_intersect_3_object()(tri0, tri1);
}

Standard_Boolean 
tnbLib::Geo_Tools::IsCcwOrder_cgal
(
	const std::vector<Pnt2d>& thePts
)
{
	Polygon_2 poly;
	for (const auto& x : thePts)
	{
		poly.push_back(Point_2(x.X(), x.Y()));
	}

	const bool IsClockwise = poly.orientation() == CGAL::COUNTERCLOCKWISE;
	return IsClockwise;
}

Standard_Boolean 
tnbLib::Geo_Tools::IsSimple_cgal
(
	const std::vector<Pnt2d>& thePts
)
{
	Polygon_2 poly;
	for (const auto& x : thePts)
	{
		poly.push_back(Point_2(x.X(), x.Y()));
	}
	return poly.is_simple();
}

tnbLib::Pnt3d 
tnbLib::Geo_Tools::ProjectToPlane_cgal
(
	const Pnt3d & thePoint, 
	const gp_Pln & thePlane
)
{	
	auto[a, b, c, d] = GetCoefficients(thePlane);
	const Plane_3 plane(a, b, c, d);
	const Point_3 pt(thePoint.X(), thePoint.Y(), thePoint.Z());

	const auto proj = plane.projection(pt);
	return { proj.x(), proj.y(), proj.z() };
}

tnbLib::Pnt2d 
tnbLib::Geo_Tools::ProjectToLine_cgal
(
	const Pnt2d & pt,
	const Entity2d_Line & line
)
{
	const auto l = get_cgal_line(line);
	const auto prj = l.projection(get_cgal_point(pt));
	return get_point(prj);
}

tnbLib::Pnt2d 
tnbLib::Geo_Tools::ProjectToLine_cgal
(
	const Pnt2d & pt,
	const Entity2d_LineRef & line
)
{
	const auto l = get_cgal_line(line);
	return get_point(l.projection(get_cgal_point(pt)));
}

std::shared_ptr<tnbLib::Geo_Tools::IntersectEntity2d> 
tnbLib::Geo_Tools::Intersection_cgal
(
	const Entity2d_Segment & theSeg0,
	const Entity2d_Segment & theSeg1
)
{
	const CGAL::cpp11::result_of<Intersect_2(Segment_2, Segment_2)>::type
		result = intersection(get_cgal_segment(theSeg0), get_cgal_segment(theSeg1));
	if (result)
	{
		if (const Segment_2* s = std::get_if<Segment_2>(&*result))
		{
			return std::make_shared<SegmentIntersectEntity2d>(Entity2d_Segment{
				get_point(s->point(0)), get_point(s->point(1))
			});
		}
		return std::make_shared<PointIntersectEntity2d>(get_point(*std::get_if<Point_2>(&*result)));
	}
	return {};
}

std::shared_ptr<tnbLib::Geo_Tools::IntersectEntity2d>
tnbLib::Geo_Tools::Intersection_cgal
(
	const Entity2d_Line & theLine0,
	const Entity2d_Line & theLine1
)
{
	const CGAL::cpp11::result_of<Intersect_2(Line_2, Line_2)>::type
		result = intersection(get_cgal_line(theLine0), get_cgal_line(theLine1));
	if (result)
	{
		if (const Line_2* l = std::get_if<Line_2>(&*result))
		{
			return std::make_shared<LineIntersectEntity2d>(Entity2d_Line{ get_point(l->point()), get_dir(l->direction()) });
		}
		return std::make_shared<PointIntersectEntity2d>(get_point(*std::get_if<Point_2>(&*result)));
	}
	return {};
}

std::shared_ptr<tnbLib::Geo_Tools::IntersectEntity2d>
tnbLib::Geo_Tools::Intersection_cgal
(
	const Entity2d_LineRef& theLine0,
	const Entity2d_LineRef& theLine1
)
{
	const CGAL::cpp11::result_of<Intersect_2(Line_2, Line_2)>::type
		result = intersection(get_cgal_line(theLine0), get_cgal_line(theLine1));
	if (result)
	{
		if (const Line_2* l = std::get_if<Line_2>(&*result))
		{
			return std::make_shared<LineIntersectEntity2d>(Entity2d_Line{ get_point(l->point()), get_dir(l->direction()) });
		}
		return std::make_shared<PointIntersectEntity2d>(get_point(*std::get_if<Point_2>(&*result)));
	}
	return {};
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo_Tools::Intersecction_cgal
(
	const Entity2d_Triangle & theTri0,
	const Entity2d_Triangle & theTri1
)
{
	const auto tri0 = get_cgal_triangle(theTri0);
	const auto tri1 = get_cgal_triangle(theTri1);

	const CGAL::cpp11::result_of<Intersect_2(Triangle_2, Triangle_2)>::type
		result = intersection(tri0, tri1);
	if (result)
	{
		std::vector<Pnt2d> pnts;
		if (const Point_2* p = std::get_if<Point_2>(&*result))
		{
			pnts.reserve(1);
			pnts.push_back(get_point(*p));
			return pnts;
		}
		if (const Segment_2* s = std::get_if<Segment_2>(&*result))
		{
			pnts.reserve(2);
			pnts.push_back(get_point(s->point(0)));
			pnts.push_back(get_point(s->point(1)));
			return pnts;
		}
		if (const Triangle_2* t = std::get_if<Triangle_2>(&*result))
		{
			pnts.reserve(3);
			pnts.push_back(get_point(t->vertex(0)));
			pnts.push_back(get_point(t->vertex(1)));
			pnts.push_back(get_point(t->vertex(2)));
			return pnts;
		}
		const std::vector<Point_2>* v = std::get_if<std::vector<Point_2>>(&*result);
		pnts.reserve(v->size());
		for (const auto& x : *v)
		{
			pnts.push_back(get_point(x));
		}
		return pnts;
	}
	return {};
}

Standard_Boolean 
tnbLib::Geo_Tools::IsIntersect_cgal
(
	const Entity3d_SegmentRef & theSeg,
	const Entity3d_Triangle & theTri
)
{
	const auto result = intersection(get_cgal_segment(theSeg), get_cgal_triangle(theTri));
	return static_cast<Standard_Boolean>(result);
}

std::pair<tnbLib::Pnt2d, Standard_Boolean> 
tnbLib::Geo_Tools::CalcIntersectionPoint_cgal
(
	const Entity2d_Ray& theRay1,
	const Entity2d_Ray& theRay2
)
{
	const auto r0 = get_cgal_ray(theRay1);
	const auto r1 = get_cgal_ray(theRay2);

	const CGAL::cpp11::result_of<Intersect_2(Ray_2, Ray_2)>::type
		result = intersection(r0, r1);
	if (result)
	{
		if (const Point_2* p = std::get_if<Point_2>(&*result))
		{
			return { get_point(*p), Standard_True };
		}
		return { Pnt2d(0, 0), Standard_False };
	}
	return { Pnt2d(0, 0), Standard_False };
}

//std::shared_ptr<tnbLib::Entity2d_Polygon> 
//tnbLib::Geo_Tools::Intersection_cgal(const gp_Pln& thePlane, const Entity3d_Box& theBox)
//{
//	return std::shared_ptr<Entity2d_Polygon>();
//}