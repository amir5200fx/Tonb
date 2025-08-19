#pragma once
namespace tnbLib
{
	template<class SurfPln>
	inline std::vector<std::shared_ptr<typename Cad_SingularZone<SurfPln>::curveType>>
		Cad_SingularZone<SurfPln>::Horizons() const
	{
		std::vector<std::shared_ptr<curveType>> horizons;
		horizons.reserve(NbHorizons());
		for (Standard_Integer i = 0; i < NbHorizons(); i++)
		{
			auto horizon = Horizon(i);
			horizons.push_back(std::move(horizon));
		}
		return std::move(horizons);
	}

	template<class SurfPln>
	inline std::vector<std::shared_ptr<typename Cad_SingularZone<SurfPln>::curveType>>
		Cad_SingularZone<SurfPln>::RetrieveHorizons
		(
			const std::vector<std::shared_ptr<Cad_SingularZone<SurfPln>>>& theZones
		)
	{
		std::vector<std::shared_ptr<curveType>> horizons;
		for (const auto& x : theZones)
		{
			Debug_Null_Pointer(x);
			auto hs = x->Horizons();
			for (auto& h : hs)
			{
				horizons.push_back(std::move(h));
			}
		}
		return std::move(horizons);
	}
}