#include <Aft2d_CoreBaseSurface.hxx>

#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Aft2d_CoreBaseSurface::mySort tnbLib::Aft2d_CoreBaseSurface::Sort;

template<>
void tnbLib::Aft2d_CoreBaseSurface::AddOptimumNodeTo
(
	std::vector<std::shared_ptr<tnbLib::Aft2d_NodeSurface>>& theNodes
)
{
	Aft2d_FrontSurfaceInfo::SetTempoNode
	(
		std::make_shared<Aft2d_NodeSurface>
		(
			Aft2d_FrontSurfaceInfo::NodeCounter() + 1,
			Aft2d_FrontSurfaceInfo::Coord()
			)
	);

	Debug_Null_Pointer(Aft2d_FrontSurfaceInfo::TempoNode());
	theNodes.push_back(Aft2d_FrontSurfaceInfo::TempoNode());

	auto pt = MetricMap()->CalcCoord3D(Aft2d_FrontSurfaceInfo::Coord());
	Aft2d_FrontSurfaceInfo::TempoNode()->SetCoord3D(std::move(pt));

	Aft2d_FrontSurfaceInfo::AppendedNode() = Standard_True;
}

Standard_Boolean 
tnbLib::Aft2d_CoreBaseSurface::IsNewPointCandidate
(
	const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theEffectives
) const
{
	if (frontInfo::AlgCondition() IS_EQUAL Aft_AlgCondition::Repair)
	{
		return Standard_False;
	}

	Debug_Null_Pointer(frontInfo::CurrentFront());

	auto factor = frontInfo::MinDistFactor();
	Debug_If_Condition(factor <= 0.);

	Debug_Null_Pointer(MetricMap());
	const auto& sizeMap = *MetricMap();

	const auto& pt = frontInfo::Coord();
	auto pt3d = sizeMap.CalcCoord3D(pt);

	for (const auto& x : theEffectives)
	{
		Debug_Null_Pointer(x);
		const auto& edge = *x;

		const auto& n0 = edge.Node0();
		const auto& n1 = edge.Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto sqDis = Geo_Tools::SquareDistance_cgal(pt3d, n0->Coord3D(), n1->Coord3D());
		auto length = factor * edge.CharLength();
		auto criteria = length * length;

		if (sqDis < criteria)
		{
			return Standard_False;
		}
	}

	const auto& edge = *frontInfo::CurrentFront();
	const auto& n0 = edge.Node0();
	const auto& n1 = edge.Node1();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);

	auto sqDis = Geo_Tools::SquareDistance_cgal(pt3d, n0->Coord3D(), n1->Coord3D());
	auto length = factor * edge.CharLength();
	auto criteria = length * length;

	if (sqDis < criteria)
	{
		return Standard_False;
	}
}