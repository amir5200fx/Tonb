#include <Entity2d_PolygonTools.hxx>

#include <Geo_CmptLib.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Polygon.hxx>

tnbLib::Entity2d_PolygonOrientation 
tnbLib::Entity2d_PolygonTools::GetOrientation
(
	const Entity2d_Triangle & theTri
)
{
	const auto poly = Geo_Tools::GetPolygon(theTri);
	return GetOrientation(*poly);
}

tnbLib::Entity2d_PolygonOrientation 
tnbLib::Entity2d_PolygonTools::GetOrientation
(
	const Entity_Triangle<const Pnt2d&>& theTri
)
{
	const auto poly = Geo_Tools::GetPolygon(theTri);
	return GetOrientation(*poly);
}

tnbLib::Entity2d_PolygonOrientation
tnbLib::Entity2d_PolygonTools::GetOrientation
(
	const Entity2d_Polygon & thePolygon
)
{
	Standard_Real sum = 0;
	const auto& pnts = thePolygon.Points();
	for (size_t i = 1; i < pnts.size(); i++)
	{
		const auto& p0 = pnts[i - 1];
		const auto& p1 = pnts[i];

		sum += Geo_CmptLib::Determinant(p0, p1);
	}
	return (sum > 0 ? Entity2d_PolygonOrientation::ccw : Entity2d_PolygonOrientation::cw);
}