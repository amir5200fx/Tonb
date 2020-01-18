#include <Geo_Tools.hxx>

#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\Segment_2.h>
#include <CGAL\Segment_3.h>
#include <CGAL\Polygon_2.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
static Kernel cgal_object;

typedef Kernel::Segment_2 Segment_2;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Vector_2 Vector_2;

typedef Kernel::Segment_3 Segment_3;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector_3;
typedef Kernel::Triangle_3 Triangle_3;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
//CGAL_HEADER_ONLY

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
	Vector_3 ad(theP2.X() - theQ.X(), theP2.Y() - theQ.Y(), theP2.Z() - theQ.Z());
	Vector_3 bd(theP2.X() - theP0.X(), theP2.Y() - theP0.Y(), theP2.Z() - theP0.Z());
	Vector_3 cd(theP2.X() - theP1.X(), theP2.Y() - theP1.Y(), theP2.Z() - theP1.Z());

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