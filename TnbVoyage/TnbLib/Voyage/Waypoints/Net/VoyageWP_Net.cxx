#include <VoyageWP_Net.hxx>

#include <Entity2d_Polygon.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::VoyageWP_Net::Node::Size() const
{
	return Standard_Integer(theNexts_.size());
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
	auto iter = theNexts_.find(theIndex);
	if (iter IS_EQUAL theNexts_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree." << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
	theNexts_.erase(iter);
}

Standard_Integer 
tnbLib::VoyageWP_Net::InterNode::StarboardSize() const
{
	return Standard_Integer(theStarboards_.size());
}

Standard_Integer 
tnbLib::VoyageWP_Net::InterNode::PortSize() const
{
	return Standard_Integer(thePorts_.size());
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
	auto iter = theStarboards_.find(theIndex);
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
	auto iter = thePorts_.find(theIndex);
	if (iter IS_EQUAL thePorts_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree." << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
	thePorts_.erase(iter);
}

Standard_Integer 
tnbLib::VoyageWP_Net::NbNodes() const
{
	return Standard_Integer(theNodes_.size());
}

std::vector<std::shared_ptr<tnbLib::VoyageWP_Net::Node>>
tnbLib::VoyageWP_Net::Waypoints
(
	const Standard_Integer theIndex
) const
{
	if(NOT INSIDE(theIndex,0,theNodes_.size()-1))
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
	auto node = std::dynamic_pointer_cast<InterNode>(ref);
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
tnbLib::VoyageWP_Net::RetrieveWaypoints
(
	const Standard_Integer theIndex, 
	const Standard_Integer fromStar,
	const Standard_Integer toPort
)
{
	auto all_wpts = Waypoints(theIndex);
	std::vector<std::shared_ptr<Node>> wps;
	wps.reserve(toPort - fromStar + 1);
	forThose(id, fromStar, toPort)
	{
		wps.emplace_back(all_wpts.at(id));
	}
	return std::move(wps);
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
