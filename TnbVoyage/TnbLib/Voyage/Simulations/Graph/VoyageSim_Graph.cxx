#include <VoyageSim_Graph.hxx>

#include <Pnt3d.hxx>
#include <TecPlot.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean
tnbLib::VoyageSim_Graph::Node::IsDeadend() const
{
	return theNexts_.empty();
}

void tnbLib::VoyageSim_Graph::Node::SetNext
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Edge>& theEdge
)
{
	auto paired = std::make_pair(theIndex, theEdge);
	if (NOT theNexts_.insert(std::move(paired)).second)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "duplicate data has been detected." << endl
			<< " - id: " << theIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::VoyageSim_Graph::Node::RemoveNext(const Standard_Integer theIndex)
{
	const auto iter = theNexts_.find(theIndex);
	if (iter IS_EQUAL theNexts_.end())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " The item is not in the tree." << endl
			<< " - id: " << theIndex << endl
			<< abort(FatalError);
	}
	theNexts_.erase(iter);
}

const std::shared_ptr<tnbLib::VoyageSim_Graph::Node>& tnbLib::VoyageSim_Graph::Edge::Node0() const
{
	return theNodes_.at(0);
}

const std::shared_ptr<tnbLib::VoyageSim_Graph::Node>& tnbLib::VoyageSim_Graph::Edge::Node1() const
{
	return theNodes_.at(1);
}

void tnbLib::VoyageSim_Graph::Edge::SetNode0(const std::shared_ptr<Node>& theNode)
{
	theNodes_.at(0) = theNode;
}

void tnbLib::VoyageSim_Graph::Edge::SetNode0(std::shared_ptr<Node>&& theNode)
{
	theNodes_.at(0) = std::move(theNode);
}

void tnbLib::VoyageSim_Graph::Edge::SetNode1(const std::shared_ptr<Node>& theNode)
{
	theNodes_.at(1) = theNode;
}

void tnbLib::VoyageSim_Graph::Edge::SetNode1(std::shared_ptr<Node>&& theNode)
{
	theNodes_.at(1) = std::move(theNode);
}

std::vector<std::shared_ptr<tnbLib::VoyageSim_Graph::Node>>
tnbLib::VoyageSim_Graph::RetrieveNodes() const
{
	static auto cmp = [](const std::shared_ptr<Node>& n0, const std::shared_ptr<Node>& n1)
	{
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		return n0->Index() < n1->Index();
	};
	std::set<std::shared_ptr<Node>, decltype(cmp)> compact(cmp);
	for (const auto&[id, edge]:theEdges_)
	{
		Debug_Null_Pointer(edge);
		compact.insert(edge->Node0());
		compact.insert(edge->Node1());
	}
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(compact.size());
	std::copy(compact.begin(), compact.end(), std::back_inserter(nodes));
	return std::move(nodes);
}

void tnbLib::VoyageSim_Graph::ExportToPlt(OFstream& theFile) const
{
	const auto nodes = RetrieveNodes();
	std::map<Standard_Integer, Standard_Integer> compact;
	Standard_Integer k = 0;
	for (const auto& x:nodes)
	{
		Debug_Null_Pointer(x);
		compact.insert({ x->Index(),++k });
	}
	std::vector<Pnt3d> coords;
	coords.reserve(nodes.size());
	for (const auto& n: nodes)
	{
		Debug_Null_Pointer(n);
		coords.emplace_back(n->Coord().X(), n->Coord().Y(), n->Time());
	}
	std::vector<connectivity::dual> ids;
	ids.reserve(theEdges_.size());
	for (const auto& [i, edge] : theEdges_)
	{
		Debug_Null_Pointer(edge);
		const auto& n0 = edge->Node0();
		const auto& n1 = edge->Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		connectivity::dual id;
		id.Value(0) = compact.at(n0->Index());
		id.Value(1) = compact.at(n1->Index());
		ids.emplace_back(std::move(id));
	}
	Io::ExportMesh(coords, ids, theFile);
}
