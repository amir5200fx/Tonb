#include <VoyageSim_GetGraphNode.hxx>

#include <VoyageSim_MinFuel.hxx>
#include <VoyageSim_Graph.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Box.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::VoyageSim_Graph::Node>>
tnbLib::VoyageSim_GetGraphNode::Find(
	const std::pair<Position, Time>& thePaired, const Standard_Real theRadius) const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	auto coord = ConvertToPnt3d(thePaired);
	std::vector<std::shared_ptr<Node>> items;
	theEngine_->GeometrySearch(theRadius, coord, items);
	std::vector<std::shared_ptr<VoyageSim_Graph::Node>> nodes;
	for (const auto& x: items)
	{
		Debug_Null_Pointer(x);
		nodes.emplace_back(x->node);
	}
	return std::move(nodes);
}

void tnbLib::VoyageSim_GetGraphNode::Perform()
{
	if (NOT Simulation())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No simulation has been found." << endl
			<< abort(FatalError);
	}
	const auto& sim = Simulation();
	const auto& graph = sim->Graph();
	if (NOT graph)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No graph has been found." << endl
			<< abort(FatalError);
	}
	std::vector<Pnt3d> coords;
	{
		const auto points = graph->RetrieveTempPositions();
		coords.reserve(points.size());
		for (const auto& x: points)
		{
			coords.emplace_back(VoyageSim_Graph::ConvertToPnt3d(x));
		}
	}
	auto bound_box = Geo_BoxTools::GetBox(coords, 0);
	bound_box.Expand(bound_box.Diameter() * 1.0E-4);
	theEngine_ = std::make_shared<Geo_AdTree<std::shared_ptr<Node>>>();
	theEngine_->SetGeometryRegion(bound_box);
	theEngine_->SetGeometryCoordFunc
	(
		[](const std::shared_ptr<Node>& n) -> const Pnt3d&
		{
			const auto& node = n->node;
			const auto& pos = node->Coord();
			return Pnt3d(pos.X(), pos.Y(), node->Time());
		}
	);
	for (const auto& x: graph->RetrieveNodes())
	{
		Debug_Null_Pointer(x);
		Node node = { x };
		theEngine_->InsertToGeometry(std::make_shared<Node>(std::move(node)));
	}
	Change_IsDone() = Standard_True;
}

tnbLib::Pnt3d tnbLib::VoyageSim_GetGraphNode::ConvertToPnt3d(const std::pair<Position, Time>& thePaired)
{
	auto [pos, time] = thePaired;
	Pnt3d pt{ pos.value.X(), pos.value.Y(), time.value };
	return std::move(pt);
}
