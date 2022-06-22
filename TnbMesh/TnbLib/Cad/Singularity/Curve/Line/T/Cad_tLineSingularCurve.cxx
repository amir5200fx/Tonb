#include <Cad_tLineSingularCurve.hxx>

#include <Aft2d_tSegmentLineEdge.hxx>
#include <TModel_Tools.hxx>
#include <TModel_Surface.hxx>
#include <TModel_ParaCurve.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

template<>
std::pair
<
	std::shared_ptr<tnbLib::Aft2d_tPlnCurveSurface>,
	std::shared_ptr<tnbLib::Aft2d_tPlnCurveSurface>
>
tnbLib::Cad_tLineSingularCurve::Split(const Standard_Real x) const
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
	auto C0 = std::make_shared<Cad_tLineSingularCurve>(std::move(c0));
	auto C1 = std::make_shared<Cad_tLineSingularCurve>(std::move(c1));
	auto t = std::make_pair(std::move(C0), std::move(C1));
	return std::move(t);
}

template<>
Standard_Real
tnbLib::Cad_tLineSingularCurve::ProjectAt
(
	const Pnt3d& thePnt,
	const TModel_Surface& thePatch
) const
{
	if (NOT Paired3d())
	{
		FatalErrorIn(FunctionSIG)
			<< "no paired curve has been found." << endl
			<< abort(FatalError);
	}

	gp_Pnt pp1;
	auto fp = Paired3d()->Value(Paired3d()->FirstParameter());
	auto lp = Paired3d()->Value(Paired3d()->LastParameter());

	GeomAPI_ProjectPointOnCurve CurveProjector;
	CurveProjector.Init(thePnt, Paired3d());

	CurveProjector.Perform(thePnt);

	if (NOT CurveProjector.NbPoints())
	{
		auto d1 = Distance(fp, thePnt);
		auto d2 = Distance(lp, thePnt);

		if (d1 < d2)
		{
			pp1 = fp;
		}
		else
		{
			pp1 = lp;
		}
	}
	else
	{
		pp1 = CurveProjector.NearestPoint();
	}

	const auto& b = thePatch.ParaBoundingBox();
	Standard_Real umin, umax, vmin, vmax;
	b.GetBound(0, umin, umax);
	b.GetBound(1, vmin, vmax);

	GeomAPI_ProjectPointOnSurf SurfProjector;
	SurfProjector.Init(pp1, TModel_Tools::RetrieveGeometry(thePatch), umin, umax, vmin, vmax);
	SurfProjector.Perform(pp1);

	if (NOT SurfProjector.NbPoints())
	{
		FatalErrorIn("Pnt2d ProjectAt(const Pnt3d& thePt) const") << endl
			<< "Failed to project the point onto the surface!" << endl
			<< abort(FatalError);
	}

	Standard_Real u, v;
	SurfProjector.LowerDistanceParameters(u, v);

	auto pp = gp_Pnt2d(u, v);
	auto fpp = Curve()->Value(Curve()->FirstParameter());
	auto lpp = Curve()->Value(Curve()->LastParameter());

	Geom2dAPI_ProjectPointOnCurve Curve2dProjector;
	Curve2dProjector.Init(gp_Pnt2d(u, v), Curve()->Geometry());

	if (NOT Curve2dProjector.NbPoints())
	{
		auto d1 = Distance(fpp, pp);
		auto d2 = Distance(lpp, pp);

		if (d1 < d2) return Curve()->FirstParameter();
		else return Curve()->LastParameter();
	}
	else
	{
		return Curve2dProjector.LowerDistanceParameter();
	}
}

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_tSegmentEdge>>
tnbLib::Cad_tLineSingularCurve::TopoMesh<tnbLib::Aft2d_tSegmentEdge>
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
	auto edges = Aft2d_tSegmentLineEdge::GetTopology(*poly, theCurve);

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