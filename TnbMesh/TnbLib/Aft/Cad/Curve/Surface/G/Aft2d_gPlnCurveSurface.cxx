#include <Aft2d_gPlnCurveSurface.hxx>

#include <Aft2d_gSegmentEdge.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Mesh2d_CurveAnIso.hxx>
#include <GModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::pair
<
	std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>,
	std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>
>
tnbLib::Aft2d_gPlnCurveSurface::Split
(
	const Standard_Real x
) const
{
	Debug_Null_Pointer(Curve());
	auto[c0, c1] = GModel_ParaCurve::Split(x, Curve());
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
	auto C0 = std::make_shared<Aft2d_gPlnCurveSurface>(std::move(c0));
	auto C1 = std::make_shared<Aft2d_gPlnCurveSurface>(std::move(c1));
	auto t = std::make_pair(std::move(C0), std::move(C1));
	return std::move(t);
}

template<>
Handle(Geom2d_Curve)
tnbLib::Aft2d_gPlnCurveSurface::Geometry() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->Geometry();
}

template<>
Standard_Real 
tnbLib::Aft2d_gPlnCurveSurface::FirstParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->FirstParameter();
}

template<>
Standard_Real 
tnbLib::Aft2d_gPlnCurveSurface::LastParameter() const
{
	Debug_Null_Pointer(Curve());
	return Curve()->LastParameter();
}

template<>
tnbLib::Pnt2d tnbLib::Aft2d_gPlnCurveSurface::Value(const Standard_Real x) const
{
	Debug_Null_Pointer(Curve());
	auto pt = Curve()->Value(x);
	return std::move(pt);
}

template<>
void tnbLib::Aft2d_gPlnCurveSurface::Reverse()
{
	Debug_Null_Pointer(Curve());
	Curve()->Reverse();
}

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gSegmentEdge>>
tnbLib::Aft2d_gPlnCurveSurface::TopoMesh<tnbLib::Aft2d_gSegmentEdge>
(
	const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve,
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
	auto edges = Aft2d_gSegmentEdge::GetTopology(*chain, theCurve);

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