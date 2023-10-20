#include <VoyageSim_MinFuel.hxx>

#include <VoyageSim_Graph.hxx>
#include <VoyageWP_Net.hxx>
#include <Geo_Tools.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	namespace voyageLib
	{

		// Forward Declarations
		class SuperEdge;

		class SuperNode
			: public Global_Indexed
		{

			/* Private Data*/

			std::shared_ptr<VoyageSim_Graph::Node> theNode_;

			std::map<Standard_Integer, std::weak_ptr<SuperEdge>>
				theEdges_;

		public:

			SuperNode
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<VoyageSim_Graph::Node>& theNode
			)
				: Global_Indexed(theIndex)
				, theNode_(theNode)
			{}

			// Public functions and operators

			const auto& Node() const { return theNode_; }
			const auto& Edges() const { return theEdges_; }

			Standard_Boolean IsArrival() const;

			void ImportEdge(const Standard_Integer theIndex, const std::weak_ptr<SuperEdge>&);
			
		};

		class SuperEdge
			: public Global_Indexed
		{

			/*Private Data*/

			std::shared_ptr<SuperNode> theNode0_;
			std::shared_ptr<SuperNode> theNode1_;

		public:

			// constructors

			SuperEdge
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<SuperNode>& theNode0, 
				const std::shared_ptr<SuperNode>& theNode1
			)
				: Global_Indexed(theIndex)
				, theNode0_(theNode0)
				, theNode1_(theNode1)
			{}

			// Public functions and operators

			const auto& Node0() const { return theNode0_; }
			const auto& Node1() const { return theNode1_; }
			
		};

		auto RetrieveNodes(const std::vector<std::shared_ptr<VoyageSim_Graph::Edge>>& theEdges)
		{
			static auto cmp = [](const std::shared_ptr<VoyageSim_Graph::Node>& node0, const std::shared_ptr<VoyageSim_Graph::Node>& node1)
			{
				Debug_Null_Pointer(node0);
				Debug_Null_Pointer(node1);
				return node0->Index() < node1->Index();
			};
			std::set<std::shared_ptr<VoyageSim_Graph::Node>, decltype(cmp)> compact(cmp);
			for (const auto& x:theEdges)
			{
				Debug_Null_Pointer(x);
				compact.insert(x->Node0());
				compact.insert(x->Node1());
			}
			std::vector<std::shared_ptr<VoyageSim_Graph::Node>> nodes;
			std::copy(compact.begin(), compact.end(), std::back_inserter(nodes));
			return std::move(nodes);
		}
		
		auto MakeSuperEdges(const std::vector<std::shared_ptr<VoyageSim_Graph::Edge>>& theEdges)
		{
			std::map<Standard_Integer, std::shared_ptr<SuperNode>> nodes;
			for (const auto& x: RetrieveNodes(theEdges))
			{
				Debug_Null_Pointer(x);
				nodes.insert({ x->Index(), std::make_shared<SuperNode>(x->Index(), x) });
			}
			std::vector<std::shared_ptr<SuperEdge>> edges;
			for (const auto& x: theEdges)
			{
				Debug_Null_Pointer(x);
				const auto v0 = x->Node0()->Index();
				const auto v1 = x->Node1()->Index();
				auto edge = std::make_shared<SuperEdge>(x->Index(), nodes.at(v0), nodes.at(v1));
				nodes.at(v0)->ImportEdge(edge->Index(), edge);
				//nodes.at(v1)->ImportEdge(edge->Index(), edge);
				edges.emplace_back(std::move(edge));
			}
			return std::move(edges);
		}

		auto RetrieveArrivalNodes(const std::vector<std::shared_ptr<SuperEdge>>& theEdges)
		{
			static auto cmp = [](const std::shared_ptr<SuperNode>& n0, const std::shared_ptr<SuperNode>& n1)
			{
				return n0->Index() < n1->Index();
			};
			std::set<std::shared_ptr<SuperNode>, decltype(cmp)> compact(cmp);
			for (const auto& x: theEdges)
			{
				Debug_Null_Pointer(x);
				Debug_Null_Pointer(x->Node0());
				Debug_Null_Pointer(x->Node1());
				compact.insert(x->Node0());
				compact.insert(x->Node1());
			}
			std::vector<std::shared_ptr<SuperNode>> arrivals;
			for (const auto& node: compact)
			{
				Debug_Null_Pointer(node);
				if (node->IsArrival())
				{
					arrivals.emplace_back(std::move(node));
				}
			}
			return std::move(arrivals);
		}

		auto RetrieveArrivalNodes(const std::vector<std::shared_ptr<VoyageSim_Graph::Edge>>& theEdges)
		{
			auto nodes = RetrieveArrivalNodes(MakeSuperEdges(theEdges));
			return std::move(nodes);
		}

		auto RetrieveArrivalNodes(const std::map<Standard_Integer, std::shared_ptr<VoyageSim_Graph::Edge>>& theEdges)
		{
			std::vector<std::shared_ptr<VoyageSim_Graph::Edge>> edges;
			edges.reserve(theEdges.size());
			for (const auto& [id, x] : theEdges)
			{
				edges.emplace_back(x);
			}
			auto nodes = RetrieveArrivalNodes(edges);
			return std::move(nodes);
		}
	}
}

void tnbLib::voyageLib::SuperNode::ImportEdge
(
	const Standard_Integer theIndex, 
	const std::weak_ptr<SuperEdge>& theEdge
)
{
	auto paired = std::make_pair(theIndex, theEdge);
	if (NOT theEdges_.insert(std::move(paired)).second)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " duplicate data has been found." << endl
			<< abort(FatalError);
	}
}

Standard_Boolean tnbLib::voyageLib::SuperNode::IsArrival() const
{
	return theEdges_.empty();
}

unsigned short tnbLib::VoyageSim_MinFuel::verbose(0);

Standard_Real tnbLib::VoyageSim_MinFuel::DEFAULT_MIN_VEL(0);
Standard_Real tnbLib::VoyageSim_MinFuel::DEFAULT_MAX_VEL(0);
Standard_Real tnbLib::VoyageSim_MinFuel::DEFAULT_VEL(0);

Standard_Integer tnbLib::VoyageSim_MinFuel::DEFAULT_NB_LEVELS(2);
Standard_Integer tnbLib::VoyageSim_MinFuel::DEFAULT_NB_SAMPLES(3);

Standard_Real tnbLib::VoyageSim_MinFuel::DEFAULT_TIME_STEP(0);
Standard_Real tnbLib::VoyageSim_MinFuel::DEFAULT_TIME_RES(0);
Standard_Real tnbLib::VoyageSim_MinFuel::DEFAULT_MAX_DAY(3);

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
	const Standard_Real theDt,
	const Standard_Real theMaxTime
)
{
	/*if (theMaxTime < theRange.first)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Contradictory data has been detected." << endl
			<< " - lower timeline: " << theRange.first << endl
			<< " - max. time: " << theMaxTime << endl
			<< abort(FatalError);
	}*/
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
	std::vector<Standard_Real> us;
	us.emplace_back(theRange.first);
	const auto ds = DT / static_cast<Standard_Real>(nb_segments);
	//const auto dt = 1.0 / len;
	for (Standard_Integer i = 1; i <= nb_segments; i++)
	{
		us.emplace_back(us.at(0) + i * ds);
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

Standard_Real
tnbLib::VoyageSim_MinFuel::ConvertDaysToHours(const Standard_Real theDays)
{
	return theDays * 24.0;
}

tnbLib::VoyageSim_MinFuel::VoyageSim_MinFuel()
	: theMinVel_(DEFAULT_MIN_VEL)
	, theMaxVel_(DEFAULT_MAX_VEL)
	, theVel_(DEFAULT_VEL)

	, theNbLevels_(DEFAULT_NB_LEVELS)
	, theNbSamples_(DEFAULT_NB_SAMPLES)

	, theTimeStep_(DEFAULT_TIME_STEP)
	, theTimeRes_(DEFAULT_TIME_RES)
	, theMaxDay_(DEFAULT_MAX_DAY)

	, theBaseTime_(0)

	, IsInit_(Standard_False)
{}

Standard_Real tnbLib::VoyageSim_MinFuel::MinTimeArrival() const
{
	Standard_Real time = RealLast();
	for (const auto& [id, x] : ArrivalNodes())
	{
		Debug_Null_Pointer(x);
		if (x->Time() < time)
		{
			time = x->Time();
		}
	}
	return time;
}

Standard_Real tnbLib::VoyageSim_MinFuel::MaxTimeArrival() const
{
	Standard_Real time = RealFirst();
	for (const auto& [id, x] : ArrivalNodes())
	{
		Debug_Null_Pointer(x);
		if (x->Time() > time)
		{
			time = x->Time();
		}
	}
	return time;
}

std::shared_ptr<tnbLib::VoyageSim_Graph::Node>
tnbLib::VoyageSim_MinFuel::FastestTimeArrivalNode() const
{
	std::shared_ptr<VoyageSim_Graph::Node> node;
	Standard_Real time = RealLast();
	for (const auto& [id, x] : ArrivalNodes())
	{
		Debug_Null_Pointer(x);
		if (x->Time() < time)
		{
			time = x->Time();
			node = x;
		}
	}
	return std::move(node);
}

std::shared_ptr<tnbLib::VoyageSim_Graph::Node>
tnbLib::VoyageSim_MinFuel::SlowestTimeArrivalNode() const
{
	std::shared_ptr<VoyageSim_Graph::Node> node;
	Standard_Real time = RealFirst();
	for (const auto& [id, x] : ArrivalNodes())
	{
		Debug_Null_Pointer(x);
		if (x->Time() > time)
		{
			time = x->Time();
			node = x;
		}
	}
	return std::move(node);
}

std::shared_ptr<tnbLib::VoyageSim_Graph::Node>
tnbLib::VoyageSim_MinFuel::LowestCostNode() const
{
	Standard_Real lowest = RealLast();
	std::shared_ptr<tnbLib::VoyageSim_Graph::Node> node;
	for (const auto& [id, x] : ArrivalNodes())
	{
		Debug_Null_Pointer(x);
		if (theTable_.at(x->Index()).first < lowest)
		{
			lowest = theTable_.at(x->Index()).first;
			node = x;
		}
	}
	return std::move(node);
}

std::shared_ptr<tnbLib::VoyageSim_Graph::Node> tnbLib::VoyageSim_MinFuel::SelectArrivalNode(
	const Standard_Real theETA) const
{
	const auto arrivals = ArrivalNodeList();
	auto node = SelectArrivalNode(theETA, arrivals);
	return std::move(node);
}

std::vector<std::shared_ptr<tnbLib::VoyageSim_Graph::Node>>
tnbLib::VoyageSim_MinFuel::ArrivalNodeList() const
{
	std::vector<std::shared_ptr<VoyageSim_Graph::Node>> nodes;
	for (const auto& [id, x]: theArrivals_)
	{
		nodes.emplace_back(x);
	}
	return std::move(nodes);
}

Standard_Real
tnbLib::VoyageSim_MinFuel::MinTimeArrival(const std::vector<std::shared_ptr<VoyageSim_Graph::Node>>& theNodes)
{
	Standard_Real time = RealLast();
	for (const auto& x:theNodes)
	{
		if (x->Time() < time)
		{
			time = x->Time();
		}
	}
	return time;
}

Standard_Real
tnbLib::VoyageSim_MinFuel::MaxTimeArrival(const std::vector<std::shared_ptr<VoyageSim_Graph::Node>>& theNodes)
{
	Standard_Real time = RealFirst();
	for (const auto& x : theNodes)
	{
		if (x->Time() > time)
		{
			time = x->Time();
		}
	}
	return time;
}

std::shared_ptr<tnbLib::VoyageSim_Graph::Node>
tnbLib::VoyageSim_MinFuel::SelectArrivalNode
(
	const Standard_Real theETA,
	const std::vector<std::shared_ptr<VoyageSim_Graph::Node>>& theNodes
)
{
	const auto min_time = MinTimeArrival(theNodes);
	const auto max_time = MaxTimeArrival(theNodes);
	if (NOT INSIDE(theETA, min_time, max_time))
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the ETA is not achievable!" << endl
			<< " - Please make sure you select an ETA inside the range of the predicted arrival times." << endl
			<< " - min. time of arrival: " << min_time << endl
			<< " - max. time of arrival: " << max_time << endl
			<< abort(FatalError);
	}
	std::shared_ptr<VoyageSim_Graph::Node> node;
	Standard_Real dis = RealLast();
	for (const auto& x: theNodes)
	{
		Debug_Null_Pointer(x);
		if (const auto idis = x->Time() - theETA; std::abs(idis) < dis)
		{
			dis = idis;
			node = x;
		}
	}
	return std::move(node);
}

std::vector
<
	std::tuple
	<
	tnbLib::VoyageSim_MinFuel::Location, 
	tnbLib::VoyageSim_MinFuel::Time,
	tnbLib::VoyageSim_MinFuel::Velocity
	>
> 
	tnbLib::VoyageSim_MinFuel::RetrievePath
	(
		const std::shared_ptr<VoyageSim_Graph::Node>& theNode
	) const
{
	Debug_Null_Pointer(theNode);
	std::vector<std::tuple<Location, Time, Velocity>> states;
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
		const auto prev = theTable_.at(current->Index()).second.lock();
		if (NOT prev)
		{
			states.push_back({ {current->Coord()},{current->Time()},{0} });
			break;
		}
		states.push_back({ {current->Coord()},{current->Time()},{theDist_(prev->Coord(), current->Coord()) / (current->Time() - prev->Time())} });
		current = prev;
	}
	return std::move(states);
}

void tnbLib::VoyageSim_MinFuel::Init()
{
	if (MinVel() <= 0)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No min. vel. has been assigned." << endl
			<< abort(FatalError);
	}
	if (MaxVel() <= 0)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No max. vel. has been assigned." << endl
			<< abort(FatalError);
	}
	if (Vel() <= 0)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No vel. has been assigned." << endl
			<< abort(FatalError);
	}
	if (TimeStep() <= 0)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No time step has been assigned." << endl
			<< abort(FatalError);
	}
	if (TimeResolution() <= 0)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No time resolution has been assigned." << endl
			<< abort(FatalError);
	}
	if (NbLevels() < 2)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid no. of levels for the velocity of the ship has been detected." << endl
			<< " - the value must be greater than 2 and the current value is: " << NbLevels() << endl
			<< abort(FatalError);
	}
	// Register the net nodes
	for (const auto& x: Net()->RetrieveNodes())
	{
		if (NOT theNetMap_.insert({ x->Index(), x }).second)
		{ // checking for any duplication in data points
			FatalErrorIn(FunctionSIG) << endl
				<< "duplicate data has been detected." << endl
				<< abort(FatalError);
		}
	}
	//Standard_Integer lev = 0;
	// Calculating the expected time arrival for each ref. node
	/*for (const auto& x: Net()->Nodes())
	{
		x->Time() = static_cast<Standard_Real>(lev) * TimeStep() + BaseTime();
		lev++;
	}*/
	const auto& nodes = Net()->Nodes();
	const auto vel = this->Vel();
	nodes.at(0)->Time() = BaseTime();
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& node0 = nodes.at(i - 1);
		const auto& node1 = nodes.at(i);
		Debug_Null_Pointer(node0);
		Debug_Null_Pointer(node1);
		const auto& p0 = node0->Coord();
		const auto& p1 = node1->Coord();
		nodes.at(i)->Time() = nodes.at(i - 1)->Time() + theDist_(p0, p1) / vel + BaseTime();
	}
	nodes.at(0)->Dist() = 0;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& node0 = nodes.at(i - 1);
		const auto& node1 = nodes.at(i);
		Debug_Null_Pointer(node0);
		Debug_Null_Pointer(node1);
		const auto& p0 = node0->Coord();
		const auto& p1 = node1->Coord();
		nodes.at(i)->Dist() = theDist_(p0, p1) + nodes.at(i - 1)->Dist();
	}
	IsInit_ = Standard_True;
}

void tnbLib::VoyageSim_MinFuel::Perform(const Standard_Integer theStart)
{
	if (NOT IsInit_)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the application is not initialized." << endl
			<< abort(FatalError);
	}
	if (MaxVel() <= MinVel())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid velocity range has been detected." << endl
			<< abort(FatalError);
	}
	/*
	 * The first thing to do is to find the starting point and put it into the pos_seed
	 * We already know the key of the point
	 */
	std::shared_ptr<VoyageWP_Net::Node> start_point;
	{
		auto iter = theNetMap_.find(theStart);
		if (iter IS_EQUAL theNetMap_.end())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " the item is not in the tree." << endl
				<< " - index: " << theStart << endl
				<< abort(FatalError);
		}
		start_point = iter->second;
	}
	std::shared_ptr<VoyageWP_Net::RefNode> current_state;
	if (auto ref = 
		std::dynamic_pointer_cast<VoyageWP_Net::RefNode>(start_point))
	{
		current_state = ref;
	}
	else
	{
		auto wp = 
			std::dynamic_pointer_cast<VoyageWP_Net::WPNode>(start_point);
		Debug_Null_Pointer(wp);
		current_state = wp->Reference().lock();
	}
	Debug_Null_Pointer(current_state);
	theGraph_ = std::make_shared<VoyageSim_Graph>();
	auto graph = theGraph_;
	const auto dpt = Net()->Departure();
	Debug_Null_Pointer(dpt);
	const auto arv = Net()->Arrival();
	Debug_Null_Pointer(arv);
	// the structure that keep the timelines for each node.
	auto& timelines = theTimeLines_;
	auto& nodes_map = theNodesMap_;
	if (verbose)
	{
		Info << endl
			<< " # Creating the global paths..." << endl;
	}
	const auto max_hour = ConvertDaysToHours(MaxDay());
	std::map<Standard_Integer, Standard_Boolean> is_dangle;
	std::shared_ptr<VoyageWP_Net::RefNode> end_pos;
	{// set the timelines for the nodes
		const auto& refs = Net()->NodesRef();
		Standard_Integer lev = 0;
		const auto vel_min = MinVel();
		const auto vel_max = MaxVel();
		Standard_Integer nb_nodes = 0;
		size_t current_ref_id = 0;
		for (const auto& x: refs)
		{
			if (current_state IS_EQUAL x)
			{
				current_ref_id = lev;
			}
			++lev;
		}
		lev = 0;
		// traverse all over the reference nodes
		for (size_t iter = 0; iter < refs.size(); iter++)
		{
			if (iter < current_ref_id)
			{
				continue; // go to the current state
			}
			const auto& x = refs.at(iter);
			Debug_Null_Pointer(x);
			if (x->Time() >= max_hour)
			{
				continue;
			}
			end_pos = x;
			if (x->IsDeparture())
			{ // if the reference node is departure
				timelines.insert({ dpt->Index(),{BaseTime()} });
				auto node =
					std::make_shared<VoyageSim_Graph::DeptNode>
					(++nb_nodes, dpt->Coord(), BaseTime()); // the start time would be zero
				Debug_Null_Pointer(node);
				nodes_map.insert({ dpt->Index(), {node} });
				is_dangle.insert({ node->Index(), Standard_False });
				x->MinTime() = BaseTime();
				x->MaxTime() = BaseTime();
				++lev;
				continue; // go for the next node
			}
			const auto min_time = x->Dist() / vel_max + BaseTime(); // calculating the lower limit of timeline
			const auto max_time = x->Dist() / vel_min + BaseTime(); // calculating the upper limit
			if (min_time IS_EQUAL max_time AND lev IS_EQUAL 0)
			{// it's a starting point
				timelines.insert({ x->Index(),{BaseTime()} });
				auto node =
					std::make_shared<VoyageSim_Graph::DeptNode>
					(++nb_nodes, x->Coord(), BaseTime()); // the start time would be zero
				Debug_Null_Pointer(node);
				nodes_map.insert({ x->Index(), {node} });
				is_dangle.insert({ node->Index(), Standard_False });
				x->MinTime() = BaseTime();
				x->MaxTime() = BaseTime();
				++lev;
				continue;
			}
			auto nodes = x->RetrieveNodes(); // retrieving all the nodes in the current stage
			if (x->IsArrival())
			{ // if the reference node is arrival
				const auto& wp = nodes.at(0); // there's just one node in the list.
				Debug_Null_Pointer(wp);
				auto times = DiscreteTime({ min_time, max_time }, TimeResolution(), max_hour); // discrete the timeline.
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
					is_dangle.insert({ node_i->Index(), Standard_True });
				}
				wp->MinTime() = FirstItem(times);
				wp->MaxTime() = LastItem(times);
				timelines.insert({ wp->Index(), std::move(times) });
				continue; // go for the next node
			}
			for (const auto& wp : nodes)
			{
				Debug_Null_Pointer(wp);
				auto times = DiscreteTime({ min_time, max_time }, TimeResolution(), max_hour); // discrete the timeline.

				{// create an empty list for position node
					nodes_map.insert({ wp->Index(),{} });
				}
				for (const auto ti : times)
				{
					auto node_i =
						std::make_shared<VoyageSim_Graph::Node>
						(++nb_nodes, wp->Coord(), ti);
					Debug_Null_Pointer(node_i);
					nodes_map.at(wp->Index()).push_back(node_i);
					is_dangle.insert({ node_i->Index(), Standard_True });
				}
				wp->MinTime() = FirstItem(times);
				wp->MaxTime() = LastItem(times);
				timelines.insert({ wp->Index(), std::move(times) });
			}
			++lev;
		}
		{// insert an empty timeline for the departure
			timelines.insert({ dpt->Index(),{} });
		}
	}
	/*
	 * Calculating the timelines for each waypoint has been completed.
	 */
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
	/*
	 * Calculate the velocity list based on the assigned NO. of levels.
	 * the value must be greater than 2
	 */
	const auto velocities = CalcVelocities();
	std::set<std::shared_ptr<VoyageWP_Net::Node>, decltype(cmp_pos)> pos_seeds(cmp_pos);
	pos_seeds.insert(start_point);
	auto& edges = graph->EdgesRef(); 
	Standard_Integer nb_edges = 0;
	auto current_time = this->BaseTime();
	while (!pos_seeds.empty())
	{
		auto current_pos = *pos_seeds.begin();
		Debug_Null_Pointer(current_pos);
		pos_seeds.erase(current_pos);  // remove the current node form the list
		if (current_pos->IsReference())
		{
			Debug_Null_Pointer(std::dynamic_pointer_cast<VoyageWP_Net::RefNode>(current_pos));
			current_time = std::dynamic_pointer_cast<VoyageWP_Net::RefNode>(current_pos)->Time();
			if (current_time >= end_pos->Time())
			{
				continue; // go for the next node
			}
		}
		else if (current_pos->IsWP())
		{
			const auto wp = std::dynamic_pointer_cast<VoyageWP_Net::WPNode>(current_pos);
			Debug_Null_Pointer(wp);
			Debug_Null_Pointer(wp->Reference().lock());
			current_time = wp->Reference().lock()->Time();
			if (current_time >= end_pos->Time())
			{
				continue; // go for the next node
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Unspecified type of node has been detected." << endl
				<< abort(FatalError);
		}
		const auto& p0 = current_pos->Coord();
		const auto& next_poses = current_pos->Nexts(); // retrieve the next nodes
		const auto& current_nodes = nodes_map.at(current_pos->Index());
		/*Standard_Boolean at_departure = Standard_False;
		if (current_pos IS_EQUAL start_point)
		{
			at_departure = Standard_True;
		}*/
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
			if (is_dangle.at(current_node->Index()))
			{
				continue; // go to the next node
			}
			const auto time0 = current_node->Time();
			Standard_Integer k = 0;
			for (const auto& [id, next_pos] : next_poses)
			{
				auto dist = next_dist.at(k++);
				const auto& next_timeline = timelines.at(id);
				//for (const auto current_vel : velocities) // check if can reach the next node in reasonable time
				const auto current_vel = LastItem(velocities);
				{
					const auto next_time = time0 + dist / current_vel;
					if (/*InsideTimeLine(next_time, next_timeline)*/ next_time<LastItem(next_timeline))
					{
						for (const auto& next_node: nodes_map.at(id))
						{
							if (next_node->Time() > next_time)
							{
								is_dangle.at(next_node->Index()) = Standard_False;
								auto edge =
									std::make_shared<VoyageSim_Graph::Edge>
									(++nb_edges, VoyageSim_Graph::Edge::Array2{ current_node, next_node });
								Debug_Null_Pointer(edge);
								current_node->SetNext(edge->Index(), edge);
								edge->SetDist(dist);
								edges.insert({ edge->Index(), edge });
							}
						}
					}
				}
			}
		}
	}
	if (verbose)
	{
		Info << endl
			<< " - Nb. of paths have been created: " << nb_edges << endl;
	}
	/*PAUSE;
	OFstream grid_3d_file("grid3d.plt");
	graph->ExportToPlt(grid_3d_file);
	std::exit(1);*/
	const auto& paths = graph->Edges();
	if (verbose)
	{
		Info << " All of the paths have been created. " << endl
			<< " - nb. of paths: " << paths.size() << endl;
	}
	std::set<std::shared_ptr<VoyageSim_Graph::Node>, decltype(cmp)> unvisited(cmp), visited(cmp);
	std::shared_ptr<VoyageSim_Graph::Node> departure;
	std::vector<std::shared_ptr<VoyageSim_Graph::Edge>> unvisited_edges;
	// gathering all unvisited nodes
	for (const auto& [id, edge] : paths)
	{
		if (auto iter = is_dangle.find(edge->Node0()->Index()); iter IS_EQUAL is_dangle.end())
		{// check if the edge is in timeline
			continue;
		}
		if (auto iter = is_dangle.find(edge->Node1()->Index()); iter IS_EQUAL is_dangle.end())
		{// check if the edge is in timeline
			continue;
		}
		Debug_Null_Pointer(edge);
		if (edge->Node0()->Index() IS_EQUAL start_point->Index())
		{
			departure = edge->Node0();
		}
		if (edge->Node1()->Index() IS_EQUAL start_point->Index())
		{
			departure = edge->Node1();
		}
		unvisited.insert(edge->Node0());
		unvisited.insert(edge->Node1());
		unvisited_edges.emplace_back(edge);
	}
	// retrieve the arrival nodes
	for (const auto& x: voyageLib::RetrieveArrivalNodes(unvisited_edges))
	{
		Debug_Null_Pointer(x);
		theArrivals_.insert({ x->Index(), x->Node() });
	}
	Debug_Null_Pointer(departure);
	auto& table = theTable_;
	for (const auto& x : unvisited)
	{// initialize the table
		Debug_Null_Pointer(x);
		if (x IS_EQUAL departure)
		{
			table.insert({ x->Index(),{0,std::shared_ptr<VoyageSim_Graph::Node>()} });
			continue;
		}
		table.insert({ x->Index(),{RealLast(),std::shared_ptr<VoyageSim_Graph::Node>()} });
	}
	//OFstream file("graph.plt");
	//graph->ExportToPlt(file);
	//std::exit(1);
	std::map<Standard_Integer, Standard_Integer> compact;
	Standard_Integer k = 0;
	for (const auto& x : graph->RetrieveNodes())
	{
		Debug_Null_Pointer(x);
		compact.insert({ x->Index(),++k });
	}
	{
		auto current = departure;
		Debug_Null_Pointer(current);
		table.at(current->Index()).first = 0;
		while (true)
		{
			Debug_Null_Pointer(current);
			auto current_value = table.at(current->Index()).first;
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
					if (table.find(next->Index()) IS_EQUAL table.end())
					{
						FatalErrorIn(FunctionSIG) << endl
							<< "the node is not in the table." << endl
							<< " - the id: " << next->Index() << endl
							<< abort(FatalError);
					}
					auto tot_resist = current_value + resist;
					if (tot_resist < val)
					{
						table.at(next->Index()) = { tot_resist,current };
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
			for (const auto& x:unvisited)
			{
				auto val = table.at(x->Index()).first;
				if ( val < smallest_val)
				{
					smallest_val = val;
					next_lev = x;
				}
			}
			current = next_lev;
		}
	}
	Change_IsDone() = Standard_True;
}
