#include <Aft2d_tPlnCurveSurface.hxx>

#include <Aft2d_tSegmentEdge.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Mesh2d_CurveAnIso.hxx>

template<>
Handle(Geom2d_Curve)
tnbLib::Aft2d_tPlnCurveSurface::Geometry() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->Geometry();
}

template<>
Standard_Real tnbLib::Aft2d_tPlnCurveSurface::FirstParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->FirstParameter();
}

template<>
Standard_Real tnbLib::Aft2d_tPlnCurveSurface::LastParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->LastParameter();
}

template<>
tnbLib::Pnt2d tnbLib::Aft2d_tPlnCurveSurface::Value(const Standard_Real x) const
{
	Debug_Null_Pointer(Curve());
	auto pt = Curve()->Value(x);
	return std::move(pt);
}

template<>
void tnbLib::Aft2d_tPlnCurveSurface::Reverse()
{
	Debug_Null_Pointer(Curve());
	Curve()->Reverse();
}

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_tSegmentEdge>>
tnbLib::Aft2d_tPlnCurveSurface::TopoMesh<tnbLib::Aft2d_tSegmentEdge>
(
	const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve,
	const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
{
	Debug_Null_Pointer(theCurve);
	Debug_Null_Pointer(theMap);
	Debug_Null_Pointer(theInfo);

	auto chain = theCurve->Mesh(theMap, theInfo);
	Debug_Null_Pointer(chain);

	const auto& sizeMap = *theMap;
	auto edges = Aft2d_tSegmentEdge::GetTopology(*chain, theCurve);

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