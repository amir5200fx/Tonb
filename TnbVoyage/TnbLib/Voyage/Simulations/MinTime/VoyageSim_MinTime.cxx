#include <VoyageSim_MinTime.hxx>

#include <VoyageSim_Graph.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>


std::map<Standard_Integer, std::shared_ptr<tnbLib::VoyageSim_Graph::Node>> tnbLib::VoyageSim_MinTime::
CalcGraphNodesMap() const
{
	Standard_Integer nbNodes = 0;
	std::map<Standard_Integer, std::shared_ptr<VoyageSim_Graph::Node>> nodesMap;
	for (const auto& x : Net()->NodesRef())
	{
		Debug_Null_Pointer(x);
		if (x->IsDeparture())
		{
			auto node =
				std::make_shared<VoyageSim_Graph::DeptNode>
				(++nbNodes, Net()->Departure()->Coord(), 0);
			nodesMap.insert({ node->Index(), node });
			continue;
		}
		// retrieving all the nodes in the current stage
		auto nodes = x->RetrieveNodes();
		if (x->IsArrival())
		{// if the reference node is arrival
			const auto& wp = nodes.at(0); // there's just one node in the list.
			Debug_Null_Pointer(wp);
			nodesMap.insert(
				{ wp->Index(),
					std::make_shared<VoyageSim_Graph::ArvalNode>
					(++nbNodes, wp->Coord(), 0) }
			);
			continue;
		}
		for (const auto& wp : nodes)
		{
			Debug_Null_Pointer(wp);
			auto node =
				std::make_shared<VoyageSim_Graph::Node>
				(++nbNodes, wp->Coord(), 0);
			Debug_Null_Pointer(node);
			nodesMap.insert({ wp->Index(), std::move(node) });
		}
	}
	return std::move(nodesMap);
}

std::vector<std::shared_ptr<tnbLib::VoyageSim_Graph::Node>> tnbLib::VoyageSim_MinTime::Nexts(
	const std::shared_ptr<VoyageWP_Net::Node>& theNode,
	const Standard_Real theTime,
	Standard_Integer& theId
) const
{
	const auto& p0 = theNode->Coord();
	std::vector<std::shared_ptr<VoyageSim_Graph::Node>> nodes;
	for (const auto& x : theNode->Nexts())
	{
		const auto& next = x.second;
		Debug_Null_Pointer(next);
		const auto& p1 = next->Coord();
		auto time =
			theCostFun_(
				{ p0,theTime },
				p1, { theDist_(p0, p1) },
				thePower_
		);
		auto node =
			std::make_shared<VoyageSim_Graph::Node>
			(++theId, p1, time.value);
		nodes.emplace_back(std::move(node));
	}
	return std::move(nodes);
}

std::shared_ptr<tnbLib::VoyageSim_Graph>
tnbLib::VoyageSim_MinTime::CalcGraph
(
	const std::shared_ptr<VoyageWP_Net::Node>& theDep,
	const std::map<Standard_Integer, std::shared_ptr<VoyageSim_Graph::Node>>& theNodesMap
) const
{
	static auto cmp =
		[](
			const std::shared_ptr<VoyageWP_Net::Node>& n0,
			const std::shared_ptr<VoyageWP_Net::Node>& n1
			)
		{
			return n0->Index() < n1->Index();
		};
	std::set<std::shared_ptr<VoyageWP_Net::Node>, decltype(cmp)> seed(cmp);
	seed.insert(theDep);
	Standard_Integer nb_edges = 0;
	auto graph = std::make_shared<VoyageSim_Graph>(); 
	auto& edges = graph->EdgesRef();
	const auto& dep = theNet_->Departure();
	const auto& arv = theNet_->Arrival();
	
	while (!seed.empty())
	{
		auto current = *seed.begin();
		
		const auto& p0 = current->Coord();
		Debug_Null_Pointer(current);
		seed.erase(current); // remove the current node form the set
		const auto& next_poses = current->Nexts();
		const auto& n0 = theNodesMap.at(current->Index());
		if (current IS_EQUAL dep)
		{
			graph->SetDeparture(n0);
		}
		if (current IS_EQUAL arv)
		{
			graph->SetArrival(n0);
		}
		std::vector<Standard_Real> next_dist;
		for (const auto& [id, next_pos] : next_poses)
		{
			Debug_Null_Pointer(next_pos);
			const auto dist = theDist_(p0, next_pos->Coord());
			next_dist.emplace_back(dist);
			seed.insert(next_pos); // adding the next nodes to the set
		}
		Standard_Integer k = 0;
		for (const auto& [id, next_pos] : next_poses)
		{
			const auto dis = next_dist.at(k++);
			const auto& n1 = theNodesMap.at(id);
			auto edge = std::make_shared<VoyageSim_Graph::Edge>
			(++nb_edges, VoyageSim_Graph::Edge::Array2{ n0, n1 });
			Debug_Null_Pointer(edge);
			n0->SetNext(edge->Index(), edge);
			edge->SetDist(dis);
			edges.insert({ edge->Index(), std::move(edge) });
		}
	}
	return std::move(graph);
}

std::vector<std::tuple<var::Location, var::Time, var::SOG>>
tnbLib::VoyageSim_MinTime::RetrievePath
(
	const std::shared_ptr<VoyageSim_Graph::Node>& theNode
) const
{
	Debug_Null_Pointer(theNode);
	std::vector<std::tuple<var::Location, var::Time, var::SOG>> states;
	auto current = theNode;
	while (true)
	{
		{
			auto iter = theTable_.find(current->Index());
			if (iter IS_EQUAL theTable_.end())
			{
				FatalErrorIn(FunctionSIG) << endl
					<< " the item isn't in the tree." << endl
					<< " - index: " << current->Index() << endl
					<< abort(FatalError);
			}
		}
		const auto tableData = theTable_.at(current->Index());
		const auto prev = tableData.second.lock();
		if (NOT prev)
		{
			states.push_back({ {current->Coord()},{current->Time()},{0}});
			break;
		}
		const auto cost = tableData.first;
		const auto deltaT = current->Time() - prev->Time();
		const auto deltaX = theDist_(prev->Coord(), current->Coord());
		const auto vel = deltaX / (deltaT);
		const auto thrust = cost / (deltaX);

		states.push_back({ {current->Coord()},{current->Time()},{vel},});
		current = prev;
	}
	return std::move(states);
}

void tnbLib::VoyageSim_MinTime::Perform()
{
	std::cout << "min time simulation..." << std::endl;
	static auto cmp =
		[](
			const std::shared_ptr<VoyageSim_Graph::Node>& n0,
			const std::shared_ptr<VoyageSim_Graph::Node>& n1
			)
		{
			return n0->Index() < n1->Index();
		};
	const auto& net = Net();
	if (NOT net)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no net has been found." << endl
			<< abort(FatalError);
	}
	const auto departure = net->Departure();
	if (NOT departure)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "found no departure!" << endl
			<< abort(FatalError);
	}
	std::cout << "calculate graph nodes map..." << std::endl;
	const auto nodesMap = CalcGraphNodesMap();
	std::cout << "graph nodes has been caculated." << std::endl;
	theArrival_ = nodesMap.at(departure->Index());
	std::cout << "calc graph..." << std::endl;
	const auto graph = CalcGraph(departure, nodesMap);
	std::cout << "the graph has been calculated." << std::endl;
	std::set<std::shared_ptr<VoyageSim_Graph::Node>, decltype(cmp)> unvisited(cmp), visited(cmp);
	for (const auto& [id, edge] : graph->Edges())
	{
		Debug_Null_Pointer(edge);
		unvisited.insert(edge->Node0());
		unvisited.insert(edge->Node1());
	}
	std::cout << "table" << std::endl;
	auto& table = theTable_;
	for (const auto& x : unvisited)
	{
		Debug_Null_Pointer(x);
		if (x IS_EQUAL graph->Departure())
		{
			table.insert({ x->Index(), {0, std::shared_ptr<VoyageSim_Graph::Node>()} });
			continue;
		}
		table.insert({ x->Index(), {RealLast(), std::shared_ptr<VoyageSim_Graph::Node>()} });
	}
	PAUSE;
	auto current = graph->Departure();
	Debug_Null_Pointer(current);
	std::cout << "current index: " << current->Index() << std::endl;
	table.at(current->Index()).first = 0;
	std::cout << "main loop" << std::endl;
	while (true)
	{
		Debug_Null_Pointer(current);
		const auto current_value = table.at(current->Index()).first;
		const auto& nexts = current->Nexts();
		std::cout << "nexts: " << nexts.size() << std::endl;
		PAUSE;
		for (const auto& [id, x] : nexts)
		{
			const auto edge = x.lock();
			Debug_Null_Pointer(edge);
			auto next = edge->Node1();
			Debug_Null_Pointer(next);
			Debug_If_Condition(current IS_EQUAL next);
			if (auto iter = unvisited.find(next); iter NOT_EQUAL unvisited.end())
			{
				auto t =
					theCostFun_
					(
						{ current->Coord(), current->Time() },
						next->Coord(),
						{ edge->Dist() },
						thePower_
					);
				std::cout << "time = " << t.value << std::endl;
				if (t.value < 0)
				{
					FatalErrorIn(FunctionSIG) << endl
						<< "Invalid value for resistance function has been detected." << endl
						<< abort(FatalError);
				}
				auto [val, prev] = table.at(next->Index());
				auto prev_node = prev.lock();
				if (table.find(next->Index()) IS_EQUAL table.end())
				{
					FatalErrorIn(FunctionSIG) << endl
						<< "the node is not in the table." << endl
						<< " - the id: " << next->Index() << endl
						<< abort(FatalError);
				}
				auto tot_cost = current_value + t.value;
				if (tot_cost < val)
				{
					table.at(next->Index()) = { tot_cost,current };
				}
			}
		}
		unvisited.erase(current);
		visited.insert(current);
		if (unvisited.empty())
		{ // check if there's no unvisited node that has been left
			break;
		}
		std::shared_ptr<VoyageSim_Graph::Node> next_lev;
		// find the smallest value
		Standard_Real smallest_val = RealLast();
		for (const auto& x : unvisited)
		{
			const auto val = table.at(x->Index()).first;
			if (val < smallest_val)
			{
				smallest_val = val;
				next_lev = x;
			}
		}
		current = next_lev;
	}
	Change_IsDone() = Standard_True;
}
