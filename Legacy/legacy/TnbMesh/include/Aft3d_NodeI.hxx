#pragma once
namespace tnbLib
{
	namespace legLib
	{
		inline auto node_comp = [](const std::shared_ptr<Aft3d_Node>& node0, const std::shared_ptr<Aft3d_Node>& node1)
		{
			return node0->Index() < node1->Index();
		};
	}
}
