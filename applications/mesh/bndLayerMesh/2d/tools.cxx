#include "tools.hxx"

#include <Aft2d_Edge.hxx>

#include <set>

std::vector<std::shared_ptr<tnbLib::Aft2d_Node>> 
tnbLib::tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<tnbLib::Aft2d_Edge>>& theEdges
)
{
	static auto cmp = [](const std::shared_ptr<Aft2d_Node>& n0, const std::shared_ptr<Aft2d_Node>& n1)
	{
		return n0->Index() < n1->Index();
	};
	std::set<std::shared_ptr<Aft2d_Node>, decltype(cmp)> comp_nodes(cmp);
	for (const auto& x : theEdges)
	{
		comp_nodes.insert(x->Node0());
		comp_nodes.insert(x->Node1());
	}
	std::vector<std::shared_ptr<Aft2d_Node>> nodes;
	std::copy(comp_nodes.begin(), comp_nodes.end(), std::back_inserter(nodes));
	std::sort
	(
		nodes.begin(),
		nodes.end(),
		[](
			const std::shared_ptr<Aft2d_Node>& n0,
			const std::shared_ptr<Aft2d_Node>& n1
			) {return n0->Index() < n1->Index(); }
	);
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::SupEdge>> 
tnbLib::tools::RetrieveSupEdges
(
	const std::vector<std::shared_ptr<tnbLib::Aft2d_Edge>>& theEdges
)
{
	auto nodes = RetrieveNodes(theEdges);
	std::vector<std::shared_ptr<SupNode>> sup_nodes;
	sup_nodes.reserve(nodes.size());
	for (const auto& x : nodes)
	{
		auto node = std::make_shared<SupNode>(x->Index(), x);
		sup_nodes.emplace_back(std::move(node));
	}
	std::vector<std::shared_ptr<SupEdge>> sup_edges;
	for (const auto& x : theEdges)
	{

	}
}