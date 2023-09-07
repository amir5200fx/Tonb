#include <VoyageWP_Net.hxx>

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