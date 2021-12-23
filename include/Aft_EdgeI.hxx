#pragma once
#include <map>
namespace tnbLib
{
	template<class EdgeTraits>
	std::vector<std::shared_ptr<typename Aft_Edge<EdgeTraits>::nodeType>>
		Aft_Edge<EdgeTraits>::RetrieveNodes
		(
			const std::vector<std::shared_ptr<Aft_Edge>>& theEdges
		)
	{
		std::map<Standard_Integer, std::shared_ptr<nodeType>> nodes_map;
		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);

			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);

			auto iter = nodes_map.find(n0->Index());
			if (iter == nodes_map.end())
			{
				auto paired = std::make_pair(n0->Index(), n0);
				nodes_map.insert(std::move(paired));
			}

			iter = nodes_map.find(n1->Index());
			if (iter == nodes_map.end())
			{
				auto paired = std::make_pair(n1->Index(), n1);
				nodes_map.insert(std::move(paired));
			}
		}

		std::vector<std::shared_ptr<nodeType>> nodes;
		nodes.reserve(nodes_map.size());
		for (auto& x : nodes_map)
		{
			nodes.push_back(std::move(x.second));
		}
		return std::move(nodes);
	}
}