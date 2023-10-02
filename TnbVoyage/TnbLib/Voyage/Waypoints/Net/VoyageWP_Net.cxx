#include <VoyageWP_Net.hxx>

#include <Entity2d_Polygon.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::VoyageWP_Net::Node::Size() const
{
	return static_cast<Standard_Integer>(theNexts_.size());
}

void tnbLib::VoyageWP_Net::Node::InsertNode
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Node>& theNode
)
{
	Global_Tools::Insert(theIndex, theNode, theNexts_);
}

void tnbLib::VoyageWP_Net::Node::RemoveNode
(
	const Standard_Integer theIndex
)
{
	const auto iter = theNexts_.find(theIndex);
	if (iter IS_EQUAL theNexts_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree." << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
	theNexts_.erase(iter);
}

void tnbLib::VoyageWP_Net::Node::FlushConnects()
{
	theNexts_.clear();
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::InterNode::RetrieveNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	for (const auto& x:theStarboards_)
	{
		nodes.emplace_back(x.second);
	}
	std::reverse(nodes.begin(), nodes.end());
	auto current = std::const_pointer_cast<Node>(shared_from_this());
	nodes.emplace_back(current);
	for (const auto& x:thePorts_)
	{
		nodes.emplace_back(x.second);
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::InterNode::RetrievePortSides() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(thePorts_.size());
	for (const auto& [id, x]:thePorts_)
	{
		nodes.push_back(x);
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::InterNode::RetrieveStarSides() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(theStarboards_.size());
	for (const auto& [id, x]: theStarboards_)
	{
		nodes.push_back(x);
	}
	return std::move(nodes);
}

Standard_Integer 
tnbLib::VoyageWP_Net::InterNode::StarboardSize() const
{
	return static_cast<Standard_Integer>(theStarboards_.size());
}

Standard_Integer 
tnbLib::VoyageWP_Net::InterNode::PortSize() const
{
	return static_cast<Standard_Integer>(thePorts_.size());
}

void tnbLib::VoyageWP_Net::InterNode::InsertToStarboard
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<WPNode>& theNode
)
{
	Global_Tools::InsertIgnoreDup(theIndex, theNode, theStarboards_);
}

void tnbLib::VoyageWP_Net::InterNode::InsertToPort
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<WPNode>& theNode
)
{
	Global_Tools::InsertIgnoreDup(theIndex, theNode, thePorts_);
}

void tnbLib::VoyageWP_Net::InterNode::RemoveFromStarboard
(
	const Standard_Integer theIndex
)
{
	const auto iter = theStarboards_.find(theIndex);
	if (iter IS_EQUAL theStarboards_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree." << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
	theStarboards_.erase(iter);
}

void tnbLib::VoyageWP_Net::InterNode::RemoveFromPort
(
	const Standard_Integer theIndex
)
{
	const auto iter = thePorts_.find(theIndex);
	if (iter IS_EQUAL thePorts_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree." << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
	thePorts_.erase(iter);
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::DepNode::RetrieveNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.emplace_back(std::const_pointer_cast<Node>(shared_from_this()));
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::ArvNode::RetrieveNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.emplace_back(std::const_pointer_cast<Node>(shared_from_this()));
	return std::move(nodes);
}

Standard_Integer 
tnbLib::VoyageWP_Net::NbNodes() const
{
	return static_cast<Standard_Integer>(theNodes_.size());
}

std::shared_ptr<tnbLib::VoyageWP_Net::Node>
tnbLib::VoyageWP_Net::Departure() const
{
	return theNodes_.at(0);
}

std::shared_ptr<tnbLib::VoyageWP_Net::Node> tnbLib::VoyageWP_Net::Arrival() const
{
	return LastItem(theNodes_);
}

std::shared_ptr<tnbLib::VoyageWP_Net::RefNode>
tnbLib::VoyageWP_Net::GetNode
(
	const Standard_Integer theIndex
) const
{
	if (NOT INSIDE(theIndex, 0, theNodes_.size() - 1))
	{
		FatalErrorIn(FunctionSIG)
			<< "bad index." << endl
			<< abort(FatalError);
	}
	return theNodes_.at(theIndex);
}

Standard_Integer
tnbLib::VoyageWP_Net::NbStarboards
(
	const Standard_Integer theIndex
) const
{
	const auto ref = GetNode(theIndex);
	Debug_Null_Pointer(ref);
	if (ref->IsInterior())
	{
		const auto interior = std::dynamic_pointer_cast<InterNode>(ref);
		Debug_Null_Pointer(interior);
		return interior->StarboardSize();
	}
	return 0;
}

Standard_Integer
tnbLib::VoyageWP_Net::NbPorts
(
	const Standard_Integer theIndex
) const
{
	const auto ref = GetNode(theIndex);
	Debug_Null_Pointer(ref);
	if (ref->IsInterior())
	{
		const auto interior = std::dynamic_pointer_cast<InterNode>(ref);
		Debug_Null_Pointer(interior);
		return interior->PortSize();
	}
	return 0;
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::RetrieveUnsortedWaypoints
(
	const Standard_Integer theIndex, 
	const Standard_Integer fromStar,
	const Standard_Integer toPort
) const
{
	std::vector<std::shared_ptr<Node>> nodes;
	auto ref = GetNode(theIndex);
	if (ref->IsInterior())
	{
		const auto interior = std::dynamic_pointer_cast<InterNode>(ref);
		Debug_Null_Pointer(interior);
		{
			const auto& wps = interior->Starboards();
			Standard_Integer id = 0;
			for (const auto& x:wps)
			{
				++id;
				if (id > fromStar)
				{
					break;
				}
				nodes.emplace_back(x.second);
			}
			if (nodes.size() > 1) std::reverse(nodes.begin(), nodes.end());
		}
		nodes.emplace_back(ref);
		{
			const auto& wps = interior->Ports();
			Standard_Integer id = 0;
			for (const auto& x : wps)
			{
				++id;
				if (id > toPort)
				{
					break;
				}
				nodes.emplace_back(x.second);
			}
		}
		return std::move(nodes);
	}
	nodes.emplace_back(ref);
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::Waypoints
(
	const Standard_Integer theIndex
) const
{
	if (NOT INSIDE(theIndex, 0, theNodes_.size() - 1))
	{
		FatalErrorIn(FunctionSIG)
			<< "the index exceeded the list" << endl
			<< abort(FatalError);
	}
	const auto ref = theNodes_.at(theIndex);
	Debug_Null_Pointer(ref);
	std::vector<std::shared_ptr<Node>> nodes;
	if (ref->IsDeparture() OR ref->IsArrival())
	{
		return std::move(nodes);
	}
	const auto node = std::dynamic_pointer_cast<InterNode>(ref);
	Debug_Null_Pointer(node);
	// gathering the starboard nodes
	for (const auto& x : node->Starboards())
	{
		nodes.emplace_back(x.second);
	}
	// gathering the port nodes
	for (const auto& x:node->Ports())
	{
		nodes.emplace_back(x.second);
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::SortedWaypoints
(
	const Standard_Integer theIndex
) const
{
	if (NOT INSIDE(theIndex, 0, theNodes_.size() - 1))
	{
		FatalErrorIn(FunctionSIG)
			<< "the index exceeded the list" << endl
			<< abort(FatalError);
	}
	const auto ref = theNodes_.at(theIndex);
	Debug_Null_Pointer(ref);
	std::vector<std::shared_ptr<Node>> nodes;
	if (ref->IsDeparture() OR ref->IsArrival())
	{
		nodes.emplace_back(ref);
		return std::move(nodes);
	}
	const auto node = std::dynamic_pointer_cast<InterNode>(ref);
	Debug_Null_Pointer(node);
	// gathering the starboard nodes
	for (const auto& x : node->Starboards())
	{
		nodes.emplace_back(x.second);
	}
	std::reverse(nodes.begin(), nodes.end());
	nodes.emplace_back(node);
	// gathering the port nodes
	for (const auto& x : node->Ports())
	{
		nodes.emplace_back(x.second);
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::RetrieveWaypoints
(
	const Standard_Integer theIndex, 
	const Standard_Integer fromStar,
	const Standard_Integer toPort
) const
{
	auto all_wpts = SortedWaypoints(theIndex);
	std::vector<std::shared_ptr<Node>> wps;
	wps.reserve(toPort - fromStar + 1);
	forThose(id, fromStar, toPort)
	{
		wps.emplace_back(all_wpts.at(id));
	}
	return std::move(wps);
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::RetrieveNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	for (const auto& x : theNodes_)
	{
		Debug_Null_Pointer(x);
		if (x->IsInterior())
		{
			const auto interior = std::dynamic_pointer_cast<InterNode>(x);
			Debug_Null_Pointer(interior);
			nodes.emplace_back(x);
			{// starboard side nodes
				const auto& star_side = interior->Starboards();
				for (const auto& n : star_side)
				{
					const auto& node = n.second;
					nodes.emplace_back(node);
				}
			}
			{// port side nodes
				const auto& port_side = interior->Ports();
				for (const auto& n : port_side)
				{
					const auto& node = n.second;
					nodes.emplace_back(node);
				}
			}
		}
		else
		{
			nodes.emplace_back(x);
		}
	}
	static auto cmp = [](const std::shared_ptr<Node>& n0, const std::shared_ptr<Node>& n1)
	{
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		return n0->Index() < n1->Index();
	};
	std::sort(nodes.begin(), nodes.end(), cmp);
	return std::move(nodes);
}

std::vector<tnbLib::Pnt2d>
tnbLib::VoyageWP_Net::RetrieveCoords() const
{
	const auto nodes = RetrieveNodes();
	std::vector<Pnt2d> coords;
	coords.reserve(nodes.size());
	for (const auto& x:nodes)
	{
		Debug_Null_Pointer(x);
		coords.emplace_back(x->Coord());
	}
	return std::move(coords);
}

std::vector<tnbLib::connectivity::dual>
tnbLib::VoyageWP_Net::RetrieveConnectivity() const
{
	std::vector<connectivity::dual> ids;
	for (const auto& x:theNodes_)
	{
		const auto& currents = x->RetrieveNodes();
		for (const auto& current:currents)
		{
			const auto i0 = current->Index();
			for (const auto& n : current->Nexts())
			{
				Debug_Null_Pointer(n.second);
				connectivity::dual d;
				d.Value(0) = i0;
				d.Value(1) = n.second->Index();
				ids.emplace_back(std::move(d));
			}
		}
	}
	return std::move(ids);
}

void tnbLib::VoyageWP_Net::FlushConnects() const
{
	const auto nodes = RetrieveNodes();
	for (const auto& x:nodes)
	{
		Debug_Null_Pointer(x);
		x->FlushConnects();
	}
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::VoyageWP_Net::RetrieveCoords
(
	const std::vector<std::shared_ptr<Node>>& theNodes
)
{
	std::vector<Pnt2d> coords;
	for (const auto& x:theNodes)
	{
		Debug_Null_Pointer(x);
		coords.emplace_back(x->Coord());
	}
	auto poly = 
		std::make_shared<Entity2d_Polygon>
	(std::move(coords), 0);
	return std::move(poly);
}
