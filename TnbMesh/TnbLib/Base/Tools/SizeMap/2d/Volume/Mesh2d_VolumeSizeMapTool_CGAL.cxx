#include <Mesh2d_VolumeSizeMapTool.hxx>

#include <Geo2d_CGALPolygonCache.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Polygon.hxx>

std::vector<tnbLib::Pnt2d> 
tnbLib::Mesh2d_VolumeSizeMapTool::RetrieveInsidePoints
(
	const std::vector<std::shared_ptr<Pnt2d>>& thePts,
	const Entity2d_Polygon& thePolygon
)
{
	Geo2d_CGALPolygonCache poly(thePolygon);
	std::vector<Pnt2d> points;
	for (const auto& x : thePts)
	{
		if (Geo_Tools::IsPointInsidePolygon(*x, poly))
		{
			points.push_back(*x);
		}
	}
	return std::move(points);
}