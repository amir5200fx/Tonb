#pragma once
#include <Standard_Integer.hxx>
#include <algorithm>
namespace tnbLib
{

	template<int Dim>
	Standard_Integer 
		MaxID
		(
			const std::vector<Entity_Connectivity<Dim>>& theC
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

	template<int Dim>
	std::vector<Entity_Connectivity<Dim>>
		CombineConnectivities
		(
			const std::vector<Entity_Connectivity<Dim>>& theC0,
			const std::vector<Entity_Connectivity<Dim>>& theC1
		)
	{
		const auto maxId = MaxID(theC0);
		std::vector<Entity_Connectivity<Dim>> connectivities;
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

	template<int Dim>
	void Entity_Connectivity<Dim>::save(TNB_oARCH_TYPE & ar, const unsigned int version) const
	{
		for (size_t i = 0; i < (size_t)Dim; i++)
		{
			ar << theV_[i];
		}
	}

	template<int Dim>
	void Entity_Connectivity<Dim>::load(TNB_iARCH_TYPE & ar, const unsigned int version)
	{
		for (size_t i = 0; i < (size_t)Dim; i++)
		{
			ar >> theV_[i];
		}
	}

}