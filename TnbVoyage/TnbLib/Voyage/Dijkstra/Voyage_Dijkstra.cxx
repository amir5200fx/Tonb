#include <Voyage_Dijkstra.hxx>

#include <VoyageFun_CostFunction.hxx>
#include <Voyage_Tools.hxx>
#include <Voyage_Graph.hxx>
#include <Voyage_Edge.hxx>
#include <Voyage_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	namespace voyageLib
	{

		auto VisitNeighbors(const std::shared_ptr<Voyage_Node>& theNode, const std::shared_ptr<VoyageFun_CostFunction>& theFun, const std::vector<Standard_Boolean>& Visited, std::vector<Standard_Real>& theDist)
		{
			auto current_dist = theDist.at(Index_Of(theNode->Index()));
			for (const auto& x : theNode->Edges())
			{
				auto edge = x.second.lock();
				Debug_Null_Pointer(edge);
				auto neighbor = Voyage_Tools::NeighborNode(theNode, edge);
				if (NOT Visited.at(Index_Of(neighbor->Index())))
				{
					auto cost = theFun->Value(edge) + current_dist;
					if (theDist.at(Index_Of(neighbor->Index())) < cost) 
						theDist.at(Index_Of(neighbor->Index())) = cost;
				}
			}
		}

		auto RetrieveNextLevel(const std::shared_ptr<Voyage_Node>& theCurrent, const std::vector<Standard_Boolean>& Visited)
		{
			std::vector<std::shared_ptr<Voyage_Node>> neighbors;
			for (const auto& x : theCurrent->Edges())
			{
				auto edge = x.second.lock();
				Debug_Null_Pointer(edge);
				auto neighbor = Voyage_Tools::NeighborNode(theCurrent, edge);
				if (NOT Visited.at(Index_Of(neighbor->Index())))
				{
					neighbors.push_back(std::move(neighbor));
				}
			}
			return std::move(neighbors);
		}
	}
}

std::shared_ptr<tnbLib::Voyage_Node> 
tnbLib::Voyage_Dijkstra::AnalyzeLevel
(
	const std::shared_ptr<Voyage_Node>& theCurrent,
	const std::vector<std::shared_ptr<Voyage_Node>>& theNextLevel,
	std::vector<Standard_Real>& theCost
) const
{
	auto current_dist = theCost.at(Index_Of(theCurrent->Index()));
	std::shared_ptr<Voyage_Node> selected;
	std::vector<std::pair<std::shared_ptr<Voyage_Node>, Standard_Real>> costs;
	for (const auto& x : theNextLevel)
	{
		Debug_Null_Pointer(x);
		auto edge = Voyage_Tools::RetrieveEdge(theCurrent, x);
		auto cost = theCost_->Value(edge) + current_dist;

		if (theCost.at(Index_Of(x->Index())) < cost)
			theCost.at(Index_Of(x->Index())) = cost;

		auto t = std::make_pair(x, cost);
		costs.push_back(std::move(t));
	}
	Standard_Real minDist = RealLast();
	for (const auto& x : costs)
	{
		if (x.second < minDist)
		{
			selected = x.first;
			minDist = x.second;
		}
	}
	return std::move(selected);
}

void tnbLib::Voyage_Dijkstra::Perform()
{
	if (NOT Graph())
	{
		FatalErrorIn(FunctionSIG)
			<< "no graph has been found." << endl
			<< abort(FatalError);
	}

	// Retrieve all vertices [7/21/2023 Payvand]
	auto vertices = Voyage_Tools::RetrieveNodes(Graph()->Edges());

	// dist[i] will hold the shortest distance from departure to i [7/21/2023 Payvand]
	std::vector<Standard_Real> dist(vertices.size(), RealLast());
	// sptSet[i] will be true if vertex i is included in shortest 
	// path tree or shortest distance from src to i is finalized [7/21/2023 Payvand]
	std::vector<Standard_Boolean> sptSet(vertices.size(), Standard_False);

	auto departure = Graph()->Departure();
	Debug_Null_Pointer(departure);

	dist.at(Index_Of(departure->Index())) = 0.0;

	auto current = Graph()->Departure();
	Debug_Null_Pointer(current);

	std::vector<std::shared_ptr<Voyage_Node>> path;
	path.push_back(current);
	while (current NOT_EQUAL Graph()->Destination())
	{
		auto nextLevel = voyageLib::RetrieveNextLevel(current, sptSet);
		if (nextLevel.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "there is no connection between departure and destination" << endl
				<< abort(FatalError);
		}
		current = AnalyzeLevel(current, nextLevel, dist);
	}
	Change_IsDone() = Standard_True;
}