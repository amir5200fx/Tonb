#include <VoyageSim_MinFuel.hxx>

#include <VoyageSim_Graph.hxx>
#include <VoyageWP_Net.hxx>
#include <Geo_Tools.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::VoyageSim_MinFuel::verbose(0);

std::vector<Standard_Real>
tnbLib::VoyageSim_MinFuel::CalcVelocities() const
{
	std::vector<Standard_Real> vels(NbLevels());
	const auto dv = (MaxVel() - MinVel()) / static_cast<Standard_Real>(NbLevels() - 1);
	for (Standard_Integer i = 0; i <= NbLevels() - 1; i++)
	{
		vels.at(i) = MinVel() + i * dv;
	}
	return std::move(vels);
}

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
	const auto ds = DT / static_cast<Standard_Real>(nb_segments);
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
	const auto velocities = CalcVelocities();
	auto graph = std::make_shared<VoyageSim_Graph>();
	const auto dpt = Net()->Departure();
	Debug_Null_Pointer(dpt);
	const auto arv = Net()->Arrival();
	Debug_Null_Pointer(arv);

	std::map<Standard_Integer, std::vector<Standard_Real>> timelines;
	std::map<Standard_Integer, std::vector<std::shared_ptr<VoyageSim_Graph::Node>>> nodes_map;
	static auto cmp_pos =
		[](
			const std::shared_ptr<VoyageWP_Net::Node>& n0,
			const std::shared_ptr<VoyageWP_Net::Node>& n1
			)
	{
		return n0->Index() < n1->Index();
	};
	static auto cmp =
		[](
			const std::shared_ptr<VoyageSim_Graph::Node>& n0,
			const std::shared_ptr<VoyageSim_Graph::Node>& n1
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
					auto node_i =
						std::make_shared<VoyageSim_Graph::ArvalNode>
						(++nb_nodes, wp->Coord(), ti);
					Debug_Null_Pointer(node_i);
					nodes_map.at(wp->Index()).push_back(node_i);
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
					auto node_i =
						std::make_shared<VoyageSim_Graph::Node>
						(++nb_nodes, wp->Coord(), ti);
					Debug_Null_Pointer(node_i);
					nodes_map.at(wp->Index()).push_back(node_i);
				}
				timelines.insert({ wp->Index(), std::move(times) });
			}
		}
	}

	std::set<std::shared_ptr<VoyageWP_Net::Node>, decltype(cmp_pos)> pos_seeds(cmp_pos);
	pos_seeds.insert(dpt);
	{// insert an empty timeline for the departure
		timelines.insert({ dpt->Index(),{} });
	}
	auto& edges = graph->EdgesRef();
	Standard_Integer nb_edges = 0;
	int kk = 0;
	while (!pos_seeds.empty())
	{
		//std::cout << " pos size = " << pos_seeds.size() << std::endl;
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
		//std::cout << "current nodes size: " << current_nodes.size() << std::endl;
		for (const auto& current_node:current_nodes)
		{
			Debug_Null_Pointer(current_node);
			const auto time0 = current_node->Time();
			//std::cout << " id = " << current_node->Index() << std::endl;
			//std::cout << "current node time = " << time0 << std::endl;
			Standard_Integer k = 0;
			for (const auto& [id, next_pos] : next_poses)
			{
				//std::cout << "pos = " << id << std::endl;
				auto dist = next_dist.at(k++);
				const auto& next_timeline = timelines.at(id);
				//for (const auto current_vel : velocities) // check if can reach the next node in reasonable time
				const auto current_vel = LastItem(velocities);
				{
					//std::cout << "current vel = " << current_vel << std::endl;
					const auto next_time = time0 + dist / current_vel;
					//std::cout << "next time = " << next_time << std::endl;
					//std::cout << std::endl;
					/*for (auto tt : next_timeline)
						std::cout << tt << ", ";
					std::cout << std::endl;
					std::cout << std::endl;*/
					if (/*InsideTimeLine(next_time, next_timeline)*/ next_time<LastItem(next_timeline))
					{
						for (const auto& next_node: nodes_map.at(id))
						{
							//std::cout << "next TIME = " << next_node->Time() << ",next time = " << next_time << std::endl;
							if (next_node->Time() > next_time)
							{
								auto edge =
									std::make_shared<VoyageSim_Graph::Edge>
									(++nb_edges, VoyageSim_Graph::Edge::Array2{ current_node, next_node });
								Debug_Null_Pointer(edge);
								current_node->SetNext(edge->Index(), edge);
								edge->SetDist(dist);
								edges.insert({ edge->Index(), edge });
							}
						}
						//break;
					}
				}
				//std::cout << std::endl;
			}
			//PAUSE;
		}
		++kk;
		//std::cout << std::endl;
		//PAUSE;
		if(kk>550)
		{
			break;
			//std::exit(1);
		}
	}
	std::cout << "nb edges = " << nb_edges << std::endl;
	//PAUSE;
	//OFstream grid_3d_file("grid3d.plt");
	//graph->ExportToPlt(grid_3d_file);
	const auto& paths = graph->Edges();
	if (verbose)
	{
		Info << " All of the paths have been created. " << endl
			<< " - nb. of paths: " << paths.size() << endl;
	}
	return;
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
