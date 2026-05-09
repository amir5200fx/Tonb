#pragma once
namespace tnbLib
{
	namespace legLib
	{
		inline auto element_comp = [](const std::shared_ptr<Aft3d_Element>& element0,
		                              const std::shared_ptr<Aft3d_Element>& element1)
		{
			return element0->Index() < element1->Index();
		};
	}
}
