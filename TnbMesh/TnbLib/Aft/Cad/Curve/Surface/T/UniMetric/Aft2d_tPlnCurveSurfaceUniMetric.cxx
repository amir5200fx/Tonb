#include <Aft2d_tPlnCurveSurfaceUniMetric.hxx>

#include <Standard_Transient.hxx>
#include <Aft2d_tSegmentEdgeUniMetric.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>
#include <Mesh2d_CurveUniMetric.hxx>
#include <TModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
Handle(Geom2d_Curve)
tnbLib::Aft2d_tPlnCurveSurfaceUniMetric::Geometry() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->Geometry();
}

template<>
Standard_Real tnbLib::Aft2d_tPlnCurveSurfaceUniMetric::FirstParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->FirstParameter();
}

template<>
Standard_Real tnbLib::Aft2d_tPlnCurveSurfaceUniMetric::LastParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->LastParameter();
}

template<>
tnbLib::Pnt2d tnbLib::Aft2d_tPlnCurveSurfaceUniMetric::Value(const Standard_Real x) const
{
	Debug_Null_Pointer(Curve());
	auto pt = Curve()->Value(x);
	return std::move(pt);
}

template<>
void tnbLib::Aft2d_tPlnCurveSurfaceUniMetric::Reverse()
{
	Debug_Null_Pointer(Curve());
	Curve()->Reverse();
}

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_tSegmentEdgeUniMetric>>
tnbLib::Aft2d_tPlnCurveSurfaceUniMetric::TopoMesh<tnbLib::Aft2d_tSegmentEdgeUniMetric>
(
	const std::shared_ptr<Aft2d_tPlnCurveSurfaceUniMetric>& theCurve,
	const std::shared_ptr<Geo2d_MetricPrcsrUniMetric>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
{
	Debug_Null_Pointer(theCurve);
	Debug_Null_Pointer(theMap);
	Debug_Null_Pointer(theInfo);

	auto chain = theCurve->Mesh(theMap, theInfo);
	Debug_Null_Pointer(chain);

	const auto& sizeMap = *theMap;
	auto edges = Aft2d_tSegmentEdgeUniMetric::GetTopology(*chain, theCurve);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		const auto& P0 = x->Node0()->Coord();
		const auto& P1 = x->Node1()->Coord();

		x->SetCharLength(theCurve->CalcCharLength(P0, P1, theMap));
		x->SetCentre(theCurve->CalcCentre(P0, P1, theMap));
	}
	return std::move(edges);
}