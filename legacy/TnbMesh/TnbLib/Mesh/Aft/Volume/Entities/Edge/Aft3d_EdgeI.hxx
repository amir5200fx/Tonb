#pragma once
namespace tnbLib
{
	namespace legLib
	{
		inline auto edge_comp = [](const std::shared_ptr<Aft3d_Edge>& edge0, const std::shared_ptr<Aft3d_Edge>& edge1)
		{
			return edge0->Index() < edge1->Index();
		};
	}
}
