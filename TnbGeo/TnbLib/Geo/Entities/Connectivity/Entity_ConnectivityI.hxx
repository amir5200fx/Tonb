#pragma once
#include <Standard_Integer.hxx>
#include <algorithm>
namespace tnbLib
{

	template<int Dim, int Reduct>
	Standard_Integer 
		MaxID
		(
			const std::vector<Entity_Connectivity<Dim, Reduct>>& theC
		)
	{
		auto maxIndex0 = IntegerFirst();
		for (const Entity_Connectivity<Dim>& x : theC)
		{
			for (size_t i = 0; i < x.nbCmpts; i++)
			{
				auto id = x.Value(i);
				if (id > maxIndex0) maxIndex0 = id;
			}
		}
		maxIndex0 = std::max(maxIndex0, 0);
		return maxIndex0;
	}

	template<int Dim, int Reduct>
	std::vector<Entity_Connectivity<Dim, Reduct>>
		CombineConnectivities
		(
			const std::vector<Entity_Connectivity<Dim, Reduct>>& theC0,
			const std::vector<Entity_Connectivity<Dim, Reduct>>& theC1
		)
	{
		const auto maxId = MaxID(theC0);
		std::vector<Entity_Connectivity<Dim, Reduct>> connectivities;
		connectivities.reserve(theC0.size() + theC1.size());

		for (const auto& x : theC0)
		{
			connectivities.push_back(x);
		}

		for (const auto& x : theC1)
		{
			auto x1 = x;
			for (size_t i = 0; i < x1.nbCmpts; i++)
			{
				x1.Value(i) += maxId;
			}
			connectivities.push_back(std::move(x1));
		}
		return std::move(connectivities);
	}

	template<int Dim, int Reduct>
	std::vector<Entity_Connectivity<Dim, Reduct>> 
		CombineConnectivities
		(
			std::vector<Entity_Connectivity<Dim, Reduct>>&& theC0,
			std::vector<Entity_Connectivity<Dim, Reduct>>&& theC1
		)
	{
		auto c0 = std::move(theC0);
		auto c1 = std::move(theC1);

		const auto maxId = MaxID(c0);
		std::vector<Entity_Connectivity<Dim, Reduct>> connectivities;
		connectivities.reserve(c0.size() + c1.size());

		for (auto& x : c0)
		{
			connectivities.push_back(std::move(x));
		}

		for (auto& x : c1)
		{
			for (size_t i = 0; i < x.nbCmpts; i++)
			{
				x.Value(i) += maxId;
			}
			connectivities.push_back(std::move(x));
		}
		return std::move(connectivities);
	}
}