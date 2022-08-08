#include <Geo_Tools.hxx>

#include <Entity2d_Triangle.hxx>
#ifdef Handle
#undef Handle
#endif // Handle
#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\Segment_2.h>
#include <CGAL\Segment_3.h>
#include <CGAL\Polygon_2.h>
#include <CGAL\Plane_3.h>
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

typedef Kernel::Segment_3 Segment_3;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector_3;
typedef Kernel::Triangle_3 Triangle_3;
typedef Kernel::Intersect_2 Intersect_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
//CGAL_HEADER_ONLY

namespace tnbLib
{

	Point_2 get_cgalPoint(const Pnt2d& p)
	{
		Point_2 pt(p.X(), p.Y());
		return std::move(pt);
	}

	Point_3 get_cgalPoint(const Pnt3d& p)
	{
		Point_3 pt(p.X(), p.Y(), p.Z());
		return std::move(pt);
	}

	Segment_2 get_cgalSegment(const Entity2d_Segment& s)
	{
		Segment_2 seg(get_cgalPoint(s.P0()), get_cgalPoint(s.P1()));
		return std::move(seg);
	}

	Segment_3 get_cgalSegment(const Entity3d_Segment& s)
	{
		Segment_3 seg(get_cgalPoint(s.P0()), get_cgalPoint(s.P1()));
		return std::move(seg);
	}

	Pnt2d get_Point(const Point_2& p)
	{
		Pnt2d pt(p.x(), p.y());
		return std::move(pt);
	}

	Pnt3d get_Point(const Point_3& p)
	{
		Pnt3d pt(p.x(), p.y(), p.z());
		return std::move(pt);
	}

	Direction_2 get_cgalDirection(const Dir2d& d)
	{
		Direction_2 dir(d.X(), d.Y());
		return std::move(dir);
	}

	Dir2d get_Dir(const Direction_2& d)
	{
		Dir2d dir(d.dx(), d.dy());
		return std::move(dir);
	}

	Line_2 get_cgalLine(const Entity2d_Line& l)
	{
		Line_2 line(get_cgalPoint(l.P()), get_cgalDirection(l.Dir()));
		return std::move(line);
	}

	Line_2 get_cgalLine(const Entity2d_LineRef& l)
	{
		Line_2 line(get_cgalPoint(l.P()), get_cgalDirection(l.Dir()));
		return std::move(line);
	}

	Triangle_2 get_cgalTriange(const Entity2d_Triangle& t)
	{
		Triangle_2 tri(get_cgalPoint(t.P0()), get_cgalPoint(t.P1()), get_cgalPoint(t.P2()));
		return std::move(tri);
	}
}

Standard_Real 
tnbLib::Geo_Tools::SquareDistance_cgal
(
	const Pnt2d & theQ,
	const Pnt2d & theP0, 
	const Pnt2d & theP1
)
{
	Point_2 Q(theQ.X(), theQ.Y());
	Segment_2 S(Point_2(theP0.X(), theP0.Y()), Point_2(theP1.X(), theP1.Y()));

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
	Point_3 Q(theQ.X(), theQ.Y(), theQ.Z());
	Segment_3 S(Point_3(theP0.X(), theP0.Y(), theP0.Z()), Point_3(theP1.X(), theP1.Y(), theP1.Z()));

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
	Point_3 Q(theQ.X(), theQ.Y(), theQ.Z());

	Triangle_3 S(Point_3(theP0.X(), theP0.Y(), theP0.Z()),
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
	Segment_3 S0(Point_3(theQ0.X(), theQ0.Y(), theQ0.Z()), Point_3(theQ1.X(), theQ1.Y(), theQ1.Z()));
	Segment_3 S1(Point_3(theP0.X(), theP0.Y(), theP0.Z()), Point_3(theP1.X(), theP1.Y(), theP1.Z()));

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
	Plane_3 pln(a, b, c, d);
	Point_3 pt(thePoint.X(), thePoint.Y(), thePoint.Z());

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
	Vector_2 dv0(theP0.X() - theQ.X(), theP0.Y() - theQ.Y());
	Vector_2 dv1(theP1.X() - theQ.X(), theP1.Y() - theQ.Y());

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

	Vector_3 ad(theQ.X() - theP0.X(), theQ.Y() - theP0.Y(), theQ.Z() - theP0.Z());
	Vector_3 bd(theQ.X() - theP1.X(), theQ.Y() - theP1.Y(), theQ.Z() - theP1.Z());
	Vector_3 cd(theQ.X() - theP2.X(), theQ.Y() - theP2.Y(), theQ.Z() - theP2.Z());

	return cgal_object.compute_determinant_3_object()(ad, bd, cd);
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
	Segment_2 S1(Point_2(theQ0.X(), theQ0.Y()), Point_2(theQ1.X(), theQ1.Y()));
	Segment_2 S2(Point_2(theP0.X(), theP0.Y()), Point_2(theP1.X(), theP1.Y()));

	return cgal_object.do_intersect_2_object()(S1, S2);
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

	bool IsClockwise = (poly.orientation() == CGAL::COUNTERCLOCKWISE);
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
	Plane_3 plane(a, b, c, d);
	Point_3 pt(thePoint.X(), thePoint.Y(), thePoint.Z());
	
	auto proj = plane.projection(pt);
	Pnt3d p(proj.x(), proj.y(), proj.z());
	return std::move(p);
}

tnbLib::Pnt2d 
tnbLib::Geo_Tools::ProjectToLine_cgal
(
	const Pnt2d & pt,
	const Entity2d_Line & line
)
{
	auto l = get_cgalLine(line);
	auto prj = l.projection(get_cgalPoint(pt));
	auto p = get_Point(prj);
	return std::move(p);
}

tnbLib::Pnt2d 
tnbLib::Geo_Tools::ProjectToLine_cgal
(
	const Pnt2d & pt,
	const Entity2d_LineRef & line
)
{
	auto l = get_cgalLine(line);
	auto prj = l.projection(get_cgalPoint(pt));
	auto p = get_Point(prj);
	return std::move(p);
}

std::shared_ptr<tnbLib::Geo_Tools::IntersectEntity2d> 
tnbLib::Geo_Tools::Intersection_cgal
(
	const Entity2d_Segment & theSeg0,
	const Entity2d_Segment & theSeg1
)
{
	auto seg0 = get_cgalSegment(theSeg0);
	auto seg1 = get_cgalSegment(theSeg1);

	CGAL::cpp11::result_of<Intersect_2(Segment_2, Segment_2)>::type
		result = intersection(seg0, seg1);
	if (result)
	{
		if (const Segment_2* s = boost::get<Segment_2>(&*result))
		{
			auto p0 = get_Point(s->point(0));
			auto p1 = get_Point(s->point(1));

			Entity2d_Segment seg(std::move(p0), std::move(p1));
			auto ent = std::make_shared<SegmentIntersectEntity2d>(std::move(seg));
			return std::move(ent);
		}
		else
		{
			const Point_2* p = boost::get<Point_2>(&*result);
			auto pt = get_Point(*p);
			auto ent = std::make_shared<PointIntersectEntity2d>(std::move(pt));
			return std::move(ent);
		}
	}
	else
	{
		auto ent = std::make_shared<IntersectEntity2d>();
		return std::move(ent);
	}
}

std::shared_ptr<tnbLib::Geo_Tools::IntersectEntity2d>
tnbLib::Geo_Tools::Intersection_cgal
(
	const Entity2d_Line & theLine0,
	const Entity2d_Line & theLine1
)
{
	auto line0 = get_cgalLine(theLine0);
	auto line1 = get_cgalLine(theLine1);

	CGAL::cpp11::result_of<Intersect_2(Line_2, Line_2)>::type
		result = intersection(line0, line1);
	if (result)
	{
		if (const Line_2* l = boost::get<Line_2>(&*result))
		{
			auto dir = get_Dir(l->direction());
			auto pt = get_Point(l->point());

			Entity2d_Line line(std::move(pt), std::move(dir));
			auto ent = std::make_shared<LineIntersectEntity2d>(std::move(line));
			return std::move(ent);
		}
		else
		{
			const Point_2* p = boost::get<Point_2>(&*result);
			auto pt = get_Point(*p);
			auto ent = std::make_shared<PointIntersectEntity2d>(std::move(pt));
			return std::move(ent);
		}
	}
	else
	{
		auto ent = std::make_shared<IntersectEntity2d>();
		return std::move(ent);
	}
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo_Tools::Intersecction_cgal
(
	const Entity2d_Triangle & theTri0,
	const Entity2d_Triangle & theTri1
)
{
	auto tri0 = get_cgalTriange(theTri0);
	auto tri1 = get_cgalTriange(theTri1);

	CGAL::cpp11::result_of<Intersect_2(Triangle_2, Triangle_2)>::type
		result = intersection(tri0, tri1);
	if (result)
	{
		std::vector<tnbLib::Pnt2d> pnts;
		if (const Point_2* p = boost::get<Point_2>(&*result))
		{
			pnts.reserve(1);
			auto pt = get_Point(*p);
			pnts.push_back(std::move(pt));
			return std::move(pnts);
		}
		else if (const Segment_2* s = boost::get<Segment_2>(&*result))
		{
			pnts.reserve(2);
			auto pt0 = get_Point(s->point(0));
			auto pt1 = get_Point(s->point(1));
			pnts.push_back(std::move(pt0));
			pnts.push_back(std::move(pt1));
			return std::move(pnts);
		}
		else if (const Triangle_2* t = boost::get<Triangle_2>(&*result))
		{
			pnts.reserve(3);
			auto pt0 = get_Point(t->vertex(0));
			auto pt1 = get_Point(t->vertex(1));
			auto pt2 = get_Point(t->vertex(2));
			pnts.push_back(std::move(pt0));
			pnts.push_back(std::move(pt1));
			pnts.push_back(std::move(pt2));
			return std::move(pnts);
		}
		else
		{
			const std::vector<Point_2>* v = boost::get<std::vector<Point_2>>(&*result);
			pnts.reserve(v->size());
			for (const auto& x : *v)
			{
				pnts.push_back(get_Point(x));
			}
			return std::move(pnts);
		}
	}
	else
	{
		return std::vector<tnbLib::Pnt2d>();
	}
}