#include <VoyageSim_MinFuel.hxx>

#include <VoyageSim_Graph.hxx>
#include <VoyageWP_Net.hxx>
#include <Geo_Tools.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<Standard_Real>
tnbLib::VoyageSim_MinFuel::DiscreteTime
(
	const std::pair<Standard_Real, Standard_Real>& theRange,
	const Standard_Real theDt)
{
	const auto DT = theRange.second - theRange.first;
	const auto len = DT / theDt; // the dimensionless length of the time
	auto nb_segments = 
		std::max
	(
		Geo_Tools::Round(len * (1.0 + EPS6)),
		Geo_Tools::Round(len * (1.0 - EPS6))
	);
	if (nb_segments < 1)
	{
		nb_segments = 1;
	}
	std::vector<Standard_Real> us(nb_segments + 1);
	FirstItem(us) = theRange.first;
	LastItem(us) = theRange.second;
	const auto ds = len / static_cast<Standard_Real>(nb_segments);
	//const auto dt = 1.0 / len;
	for (Standard_Integer i = 1; i <= nb_segments - 1; i++)
	{
		us.at(i) = us.at(0) + i * ds;
	}
	return std::move(us);
}

Standard_Boolean
tnbLib::VoyageSim_MinFuel::InsideTimeLine
(
	const Standard_Real theTime,
	const std::vector<Standard_Real>& theTimeline
)
{
	return INSIDE(theTime, FirstItem(theTimeline), LastItem(theTimeline));
}

void tnbLib::VoyageSim_MinFuel::Perform()
{
	std::vector<Standard_Real> velocities; // taking care of it later
	auto graph = std::make_shared<VoyageSim_Graph>();
	const auto dpt = Net()->Departure();
	Debug_Null_Pointer(dpt);
	const auto arv = Net()->Arrival();
	Debug_Null_Pointer(arv);

	std::map<Standard_Integer, std::vector<Standard_Real>> timelines;
	std::map<Standard_Integer, std::vector<std::shared_ptr<VoyageSim_Graph::Node>>> nodes_map;
	static auto cmp =
		[](
			const std::shared_ptr<VoyageWP_Net::Node>& n0,
			const std::shared_ptr<VoyageWP_Net::Node>& n1
			)
	{
		return n0->Index() < n1->Index();
	};
	if (verbose)
	{
		Info << endl
			<< " # Creating the global paths..." << endl;
	}
	{// set the timelines for the nodes
		const auto& refs = Net()->NodesRef();
		Standard_Integer lev = 0;
		const auto vel_min = MinVel() / Vel();
		const auto vel_max = MaxVel() / Vel();
		Standard_Integer nb_nodes = 0;
		for (const auto& x:refs)
		{
			Debug_Null_Pointer(x);
			auto ref = std::dynamic_pointer_cast<VoyageWP_Net::RefNode>(x);
			Debug_Null_Pointer(ref);
			
			if (x->IsDeparture())
			{
				timelines.insert({ dpt->Index(),{0} });
				auto node = 
					std::make_shared<VoyageSim_Graph::DeptNode>
				(++nb_nodes, dpt->Coord(), 0);
				Debug_Null_Pointer(node);
				nodes_map.insert({ dpt->Index(), {node} });
				continue;
			}
			++lev;
			const auto min_time = static_cast<Standard_Real>(lev) * TimeStep() / vel_max;
			const auto max_time = static_cast<Standard_Real>(lev) * TimeStep() / vel_min;
			auto nodes = ref->RetrieveNodes();
			if (x->IsArrival())
			{
				const auto& wp = nodes.at(0);
				Debug_Null_Pointer(wp);
				auto times = DiscreteTime({ min_time, max_time }, TimeResolution());
				{// create an empty list for position node
					nodes_map.insert({ wp->Index(),{} });
				}
				for (const auto ti : times)
				{
					auto node =
						std::make_shared<VoyageSim_Graph::ArvalNode>
						(++nb_nodes, node->Coord(), ti);
					Debug_Null_Pointer(node);
					nodes_map.at(wp->Index()).push_back(node);
				}
				timelines.insert({ wp->Index(), std::move(times) });
				continue;
			}
			for (const auto& wp:nodes)
			{
				Debug_Null_Pointer(wp);
				auto times = DiscreteTime({ min_time, max_time }, TimeResolution());
				{// create an empty list for position node
					nodes_map.insert({ wp->Index(),{} });
				}
				for (const auto ti: times)
				{
					auto node =
						std::make_shared<VoyageSim_Graph::Node>
						(++nb_nodes, node->Coord(), ti);
					Debug_Null_Pointer(node);
					nodes_map.at(wp->Index()).push_back(node);
				}
				timelines.insert({ wp->Index(), std::move(times) });
			}
		}
	}
	std::set<std::shared_ptr<VoyageWP_Net::Node>, decltype(cmp)> pos_seeds(cmp);
	pos_seeds.insert(dpt);
	{// insert an empty timeline for the departure
		timelines.insert({ dpt->Index(),{} });
	}
	Standard_Integer nb_edges = 0;
	while (!pos_seeds.empty())
	{
		auto current_pos = *pos_seeds.begin();
		Debug_Null_Pointer(current_pos);
		pos_seeds.erase(current_pos);  // remove the current node form the list
		const auto& p0 = current_pos->Coord();
		const auto& next_poses = current_pos->Nexts(); // retrieve the next nodes
		const auto& current_nodes = nodes_map.at(current_pos->Index());
		std::vector<Standard_Real> next_dist;
		for (const auto& [id, next_pos] : next_poses)
		{
			Debug_Null_Pointer(next_pos);
			const auto dist = theDist_(p0, next_pos->Coord());
			next_dist.push_back(dist);
			pos_seeds.insert(next_pos);
		}
		for (const auto& current_node:current_nodes)
		{
			Debug_Null_Pointer(current_node);
			const auto time0 = current_node->Time();
			Standard_Integer k = 0;
			for (const auto& [id, next_pos] : next_poses)
			{
				auto dist = next_dist.at(k++);
				const auto& next_timeline = timelines.at(id);
				for (const auto current_vel : velocities)
				{
					const auto next_time = time0 + dist / current_vel;
					if (InsideTimeLine(next_time, next_timeline))
					{
						for (const auto& next_node: nodes_map.at(id))
						{
							if (next_node->Time() > next_time)
							{
								auto edge =
									std::make_shared<VoyageSim_Graph::Edge>
									(++nb_edges, VoyageSim_Graph::Edge::Array2{ current_node, next_node });
								Debug_Null_Pointer(edge);
								current_node->SetNext(edge->Index(), edge);
								edge->SetDist(dist);
							}
						}
					}
				}
			}
			
		}
		
		
	}
	const auto& paths = graph->Edges();
	if (verbose)
	{
		Info << " All of the paths have been created. " << endl
			<< " - nb. of paths: " << paths.size() << endl;
	}
	std::set<std::shared_ptr<VoyageSim_Graph::Node>, decltype(cmp)> unvisited(cmp), visited(cmp);
	for (const auto& [id, edge] : paths)
	{
		Debug_Null_Pointer(edge);
		unvisited.insert(edge->Node0());
		unvisited.insert(edge->Node1());
	}
	std::map<Standard_Integer, std::pair<Standard_Real, std::weak_ptr<VoyageSim_Graph::Node>>> table;
	std::shared_ptr<VoyageSim_Graph::Node> departue;
	for (const auto& x:unvisited)
	{// initialize the table
		Debug_Null_Pointer(x);
		if (x->IsDeparture())
		{
			table.insert({ x->Index(),{0,std::shared_ptr<VoyageSim_Graph::Node>()} });
			departue = x;
			continue;
		}
		table.insert({ x->Index(),{RealLast(),std::shared_ptr<VoyageSim_Graph::Node>()} });
	}
	{
		auto current = departue;
		while (true)
		{
			Debug_Null_Pointer(current);
			const auto& nexts = current->Nexts();
			for (const auto& [id, x] : nexts)
			{
				
				auto edge = x.lock();
				Debug_Null_Pointer(edge);
				auto next = edge->Node1();
				Debug_Null_Pointer(next);
				Debug_If_Condition(next IS_EQUAL current);
				if (auto iter = unvisited.find(next); iter NOT_EQUAL unvisited.end())
				{
					auto resist =
						theResistFun_
						(
							{ current->Coord(), current->Time() },
							{ next->Coord(), next->Time() },
							edge->Dist(), NbSamples()
						);
					auto [val, prev] = table.at(next->Index());
					auto prev_node = prev.lock();
					if (NOT prev_node)
					{
						table.at(id) = { resist,current };
					}
					else
					{
						auto tot_resist = current->Value() + resist;
						if (tot_resist < next->Value())
						{
							table.at(id) = { tot_resist,current };
						}
					}
				}
			}
			unvisited.erase(current);
			visited.insert(current);
			std::shared_ptr<VoyageSim_Graph::Node> next_lev;
			// find the smallest value
			Standard_Real smallest_val = RealLast();
			for (const auto& x:unvisited)
			{
				if (x->Value() < smallest_val)
				{
					smallest_val = x->Value();
					next_lev = x;
				}
			}
			current = next_lev;
		}
	}
	Change_IsDone() = Standard_True;
}
