#include <Entity2d_PolygonTools.hxx>

#include <CGAL/Polygon_2_algorithms.h>

tnbLib::Entity2d_PolygonSide
tnbLib::Entity2d_PolygonTools::GetSide
(
	const Point & pt,
	Point * pt_begin,
	Point * pt_end,
	K traits
)
{
	switch (CGAL::bounded_side_2(pt_begin, pt_end, pt, traits))
	{
	case CGAL::ON_BOUNDED_SIDE:
	{
		//- the point is inside the polygon
		return Entity2d_PolygonSide::bounded;
	}
	case CGAL::ON_BOUNDARY:
	{
		//- the point is on the polygon boundary
		return Entity2d_PolygonSide::boundary;
	}
	case CGAL::ON_UNBOUNDED_SIDE:
	{
		//- the point is outside the polygon
		return Entity2d_PolygonSide::unbounded;
	}
	}

	//- This doesn't happen
	return Entity2d_PolygonSide::boundary;
}