#include <Cad_tPoleSingularCurve.hxx>

#include <Aft2d_tSegmentPoleEdge.hxx>
#include <TModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::pair
<
	std::shared_ptr<tnbLib::Aft2d_tPlnCurveSurface>,
	std::shared_ptr<tnbLib::Aft2d_tPlnCurveSurface>
>
tnbLib::Cad_tPoleSingularCurve::Split
(
	const Standard_Real x
) const
{
	Debug_Null_Pointer(Curve());
	auto[c0, c1] = TModel_ParaCurve::Split(x, Curve());
	if (NOT c0)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	if (NOT c1)
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is null" << endl
			<< abort(FatalError);
	}
	auto C0 = std::make_shared<Cad_tPoleSingularCurve>(std::move(c0));
	auto C1 = std::make_shared<Cad_tPoleSingularCurve>(std::move(c1));
	auto t = std::make_pair(std::move(C0), std::move(C1));
	return std::move(t);
}

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_tSegmentEdge>>
tnbLib::Cad_tPoleSingularCurve::TopoMesh<tnbLib::Aft2d_tSegmentEdge>
(
	const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve,
	const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
{
	Debug_Null_Pointer(theCurve);
	Debug_Null_Pointer(theMap);
	Debug_Null_Pointer(theInfo);

	auto poly = theCurve->Mesh(theMap, theInfo);
	Debug_Null_Pointer(poly);

	const auto& sizeMap = *theMap;
	auto edges = Aft2d_tSegmentPoleEdge::GetTopology(*poly, theCurve);

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