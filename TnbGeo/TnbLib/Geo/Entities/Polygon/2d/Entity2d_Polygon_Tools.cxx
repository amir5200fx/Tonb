#include <Entity2d_Polygon_Tools.hxx>

#include <CGAL/Polygon_2_algorithms.h>

tnbLib::Entity2d_Polygon_SIDE 
tnbLib::Entity2d_Polygon_Tools::CheckSide
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
		return Entity2d_Polygon_BOUNDED_SIDE;
	}
	case CGAL::ON_BOUNDARY: 
	{
		//- the point is on the polygon boundary
		return Entity2d_Polygon_BOUNDARY_SIDE;
	}
	case CGAL::ON_UNBOUNDED_SIDE: 
	{
		//- the point is outside the polygon
		return Entity2d_Polygon_UNBOUNDED_SIDE;
	}
	}

	//- This doesn't happen
	return Entity2d_Polygon_UNBOUNDED_SIDE;
}