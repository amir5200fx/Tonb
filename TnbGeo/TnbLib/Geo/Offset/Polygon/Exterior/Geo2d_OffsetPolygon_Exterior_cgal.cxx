#include <Geo2d_OffsetPolygon_Exterior.hxx>

#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef Handle
#undef Handle
#endif // Handle

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/create_straight_skeleton_2.h>
#include <CGAL/draw_straight_skeleton_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                   Point;
typedef CGAL::Polygon_2<K>           Polygon_2;
typedef CGAL::Straight_skeleton_2<K> Ss;

void tnbLib::Geo2d_OffsetPolygon_Exterior::Perform()
{
	if (NOT Polygon())
	{
		FatalErrorIn(FunctionSIG)
			<< " no polygon has been loaded." << endl
			<< abort(FatalError);
	}
	if (MaxOffset() <= 0)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "The offset value has been detected." << endl
			<< " - value: " << MaxOffset() << endl
			<< abort(FatalError);
	}
	Polygon_2 poly;
	for (const auto& x : Polygon()->Points())
	{
		poly.push_back(Point(x.X(), x.Y()));
	}
	if (NOT poly.is_counterclockwise_oriented())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the polygon is not counter clockwise." << endl
			<< abort(FatalError);
	}
	auto iss = 
		CGAL::create_exterior_straight_skeleton_2
		(MaxOffset(), poly);
	std::vector<Pnt2d> pts;
	pts.reserve(iss->size_of_vertices());
	auto iter = iss->vertices_begin();
	while (iter NOT_EQUAL iss->vertices_end())
	{
		const auto& coord = iter->point();
		pts.push_back({ coord.x(),coord.y() });
		iter++;
	}
	auto offset_poly = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
	theOffset_ = std::move(offset_poly);
	Change_IsDone() = Standard_True;
}