#include <Cad_ModifySingularPlane_PolygonLib.hxx>

#include <Entity2d_Polygon.hxx>

Point_2 
tnbLib::meshLib::singularity::PolygonLib::GetPoint
(
	const Pnt2d & thePt
)
{
	Point_2 coord(thePt.X(), thePt.Y());
	return std::move(coord);
}

std::shared_ptr<tnbLib::meshLib::singularity::Polygon>
tnbLib::meshLib::singularity::PolygonLib::GetWire(const Entity2d_Polygon & thePoly)
{
	const auto& pts = thePoly.Points();
	std::vector<Point_2> ptList;
	ptList.reserve(pts.size());
	for (const auto& x : pts)
	{
		auto pt = GetPoint(x);
		ptList.push_back(std::move(pt));
	}
	auto poly = std::make_shared<Polygon>(std::move(ptList));
	return std::move(poly);
}