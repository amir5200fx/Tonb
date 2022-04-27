#include <Aft2d_PlnCurve.hxx>

#include <Mesh2d_Curve.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::shared_ptr<tnbLib::Entity2d_Polygon> tnbLib::Mesh_PlnCurve_Base::Mesh
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theU0,
	const Standard_Real theU1,
	const std::shared_ptr<Geo2d_MetricPrcsr>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
)
{
	Mesh2d_Curve alg(theCurve, theU0, theU1, theMap, theInfo);

	if (NOT alg.Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "No curve has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT alg.MetricMap())
	{
		FatalErrorIn(FunctionSIG)
			<< "No size map has been loaded!" << endl
			<< abort(FatalError);
	}

	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm has not been performed!");

	const auto& mesh = alg.Mesh();
	return std::move(mesh);
}

template<>
template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>>
tnbLib::Aft2d_PlnCurve::TopoMesh<tnbLib::Aft2d_SegmentEdge>
(
	const std::shared_ptr<Aft2d_PlnCurve>& theCurve, 
	const std::shared_ptr<Geo2d_MetricPrcsr>& theMap,
	const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
{
	Debug_Null_Pointer(theCurve);
	Debug_Null_Pointer(theMap);
	Debug_Null_Pointer(theInfo);

	auto chain = theCurve->Mesh(theMap, theInfo);
	Debug_Null_Pointer(chain);

	const auto& sizeMap = *theMap;
	auto edges = Aft2d_SegmentEdge::GetTopology(*chain, theCurve);

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