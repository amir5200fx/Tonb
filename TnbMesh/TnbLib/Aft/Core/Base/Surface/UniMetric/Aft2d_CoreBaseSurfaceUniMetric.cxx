#include <Aft2d_CoreBaseSurfaceUniMetric.hxx>

tnbLib::Aft2d_CoreBaseSurfaceUniMetric::mySort tnbLib::Aft2d_CoreBaseSurfaceUniMetric::Sort;

template<>
void tnbLib::Aft2d_CoreBaseSurfaceUniMetric::AddOptimumNodeTo
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