#pragma once
#ifdef _DEBUG
#include <TnbError.hxx>
#include <OSstream.hxx>
#endif // _DEBUG
template<class CurveType>
inline Standard_Real 
tnbLib::Cad_PoleSingularCurve<CurveType>::CalcCharLength
(
	const Pnt2d &,
	const Pnt2d &,
	const std::shared_ptr<metricMap>&
) const
{
	return (Standard_Real)0;
}

template<class CurveType>
inline tnbLib::Pnt2d 
tnbLib::Cad_PoleSingularCurve<CurveType>::CalcCentre
(
	const Pnt2d & theP0,
	const Pnt2d & theP1, 
	const std::shared_ptr<metricMap>& /*theMap*/
) const
{
	auto pt = MEAN(theP0, theP1);
	return std::move(pt);
}

template<class CurveType>
inline std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::Cad_PoleSingularCurve<CurveType>::Mesh
(
	const std::shared_ptr<metricMap>& theMetricMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
) const
{
	std::vector<Pnt2d> pts;
	pts.reserve(3);

	auto p0 = CurveType::FirstCoord();
	auto p1 = CurveType::LastCoord();
	auto pm = MEAN(p0, p1);

	pts.push_back(std::move(p0));
	pts.push_back(std::move(pm));
	pts.push_back(std::move(p1));

	auto poly = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
	return std::move(poly);
}

template<class CurveType>
inline void tnbLib::Cad_PoleSingularCurve<CurveType>::CalcSubcurves() const
{
#ifdef _DEBUG
	FatalErrorIn(FunctionSIG)
		<< "It's not supposed to be called!" << endl
		<< abort(FatalError);
#endif // !_DEBUG
}