#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class CurveType>
inline std::vector<std::shared_ptr<tnbLib::Entity2d_Chain>> 
tnbLib::Cad_SingularityTopologyTools::GetChainList
(
	const std::vector<std::shared_ptr<CurveType>>& theCurves
)
{
	std::vector<std::shared_ptr<Entity2d_Chain>> chains;
	chains.reserve(theCurves.size());

	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);
		auto chain = GetChain(x->Geometry());
		chains.push_back(std::move(chain));
	}

	for (size_t i = 1; i < chains.size(); i++)
	{
		const auto& chain0 = chains.at(i - 1);
		const auto& chain1 = chains.at(i);

		Debug_Null_Pointer(chain0);
		Debug_Null_Pointer(chain1);

		const auto& pts0 = chain0->Points();
		const auto& pts1 = chain1->Points();

		Debug_If_Condition(pts0.size() NOT_EQUAL 2);
		Debug_If_Condition(pts1.size() NOT_EQUAL 2);

		pts0[1] = pts1[0] = MEAN(pts0[1], pts1[0]);
	}

	const auto& chain0 = chains[chains.size() - 1];
	const auto& chain1 = chains[0];

	auto& pts0 = chain0->Points();
	auto& pts1 = chain1->Points();

	pts0[1] = pts1[0] = MEAN(pts0[1], pts1[0]);

	return std::move(chains);
}