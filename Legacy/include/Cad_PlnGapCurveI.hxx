#pragma once
#include <Entity2d_Polygon.hxx>
template<class PlnCurve>
inline Standard_Real 
tnbLib::Cad_PlnGapCurve<PlnCurve>::CalcCharLength
(
	const Pnt2d &,
	const Pnt2d &,
	const std::shared_ptr<metricMap>&
) const
{
	return (Standard_Real)0;
}

template<class PlnCurve>
inline tnbLib::Pnt2d 
tnbLib::Cad_PlnGapCurve<PlnCurve>::CalcCentre
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const std::shared_ptr<metricMap>& /*theMap*/
) const
{
	auto pt = MEAN(theP0, theP1);
	return std::move(pt);
}

template<class PlnCurve>
inline std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::Cad_PlnGapCurve<PlnCurve>::Mesh
(
	const std::shared_ptr<metricMap>& theMetricMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
) const
{
	std::vector<Pnt2d> pts;
	pts.reserve(3);

	auto p0 = PlnCurve::FirstCoord();
	auto p1 = PlnCurve::LastCoord();
	auto pm = MEAN(p0, p1);

	pts.push_back(std::move(p0));
	pts.push_back(std::move(pm));
	pts.push_back(std::move(p1));

	auto poly = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
	return std::move(poly);
}