#include <Aft2d_gPlnCurveSurfaceUniMetric.hxx>

#include <Aft2d_gSegmentEdgeUniMetric.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>
#include <Mesh2d_CurveUniMetric.hxx>
#include <GModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
Handle(Geom2d_Curve)
tnbLib::Aft2d_gPlnCurveSurfaceUniMetric::Geometry() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->Geometry();
}

template<>
Standard_Real 
tnbLib::Aft2d_gPlnCurveSurfaceUniMetric::FirstParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->FirstParameter();
}

template<>
Standard_Real 
tnbLib::Aft2d_gPlnCurveSurfaceUniMetric::LastParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->LastParameter();
}

template<>
tnbLib::Pnt2d
tnbLib::Aft2d_gPlnCurveSurfaceUniMetric::Value(const Standard_Real x) const
{
	Debug_Null_Pointer(Curve());
	auto pt = Curve()->Value(x);
	return std::move(pt);
}

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gSegmentEdgeUniMetric>>
tnbLib::Aft2d_gPlnCurveSurfaceUniMetric::TopoMesh<tnbLib::Aft2d_gSegmentEdgeUniMetric>
(
	const std::shared_ptr<Aft2d_gPlnCurveSurfaceUniMetric>& theCurve,
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
	auto edges = Aft2d_gSegmentEdgeUniMetric::GetTopology(*chain, theCurve);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		const auto& P0 = x->Node0()->Coord();
		const auto& P1 = x->Node1()->Coord();

		x->SetCharLength(sizeMap.CalcDistance(P0, P1));
		x->SetCentre(sizeMap.CalcCentre(P0, P1));
	}
	return std::move(edges);
}