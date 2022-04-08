#pragma once
#include <Cad_SingularityTopologyTools.hxx>
#include <Merge2d_Chain.hxx>
template<class SurfType>
inline void tnbLib::Cad_SingularityTopology<SurfType>::Perform()
{
	//- There is a complexity about the curves excluding the one had retrieved from
	//- the intersection operator:
	//
	//- a wire may have a very bad geometry which lead the merging algorithm to fail
	//- so it's better to use the nature of a wire and merging the curves sequentially.
	//- In this method, we need to keep track of the equivalent chain for every curves in
	//- the solid_plane including horizon ones.

	const auto& wireList = Wires();
	std::vector<std::shared_ptr<std::vector<std::shared_ptr<parCurveType>>>>
		wires;
	wires.reserve(wireList.size());
	for (const auto& x : wireList)
	{
		Debug_Null_Pointer(x);
		auto wire = Cad_SingularityTopologyTools::RetrieveCurves<parCurveType, parWireType>(x);

		wires.push_back(std::move(wire));
	}

	auto& curveToChain = theCurveToChain_;
	for (const auto& x : wires)
	{
		Debug_Null_Pointer(x);
		auto chains = Cad_SingularityTopologyTools::GetChainList(*x);

		Standard_Integer k = 0;
		for (const auto& curve : *x)
		{
			auto paired = std::make_pair(curve, chains.at(k++));
			auto insert = curveToChain.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data has been found!" << endl
					<< abort(FatalError);
			}
		}
	}

	for (const auto& x : theHorizons_)
	{
		Debug_Null_Pointer(x);
		auto geom = x->Geometry();
		Debug_Null_Pointer(geom);

		auto chain = Cad_SingularityTopologyTools::GetChain(geom);

		auto paired = std::make_pair(x, std::move(chain));
		auto insert = curveToChain.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been found!" << endl
				<< abort(FatalError);
		}
	}

	auto& edgeToCurve = theEdgeToCurve_;
	theTopology_ = GetTopology(curveToChain, edgeToCurve);

	Change_IsDone() = Standard_True;
}

template<class SurfType>
inline std::shared_ptr<tnbLib::Geo2d_TopoChainAnalysis> 
tnbLib::Cad_SingularityTopology<SurfType>::GetTopology
(
	const std::map<std::shared_ptr<parCurveType>, std::shared_ptr<Entity2d_Chain>>& theCurves,
	std::map<std::shared_ptr<edgeType>, std::shared_ptr<parCurveType>>& theEdges
)
{
	std::vector<std::shared_ptr<Entity2d_Chain>> chains;
	std::vector<std::shared_ptr<parCurveType>> curves;
	chains.reserve(theCurves.size());
	curves.reserve(theCurves.size());

	for (const auto& x : theCurves)
	{
		chains.push_back(x.second);
		curves.push_back(x.first);
	}

	Merge2d_Chain alg;
	alg.Import(chains);

	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the application is not performed!");

	const auto& merged = alg.Merged();
	Debug_Null_Pointer(merged);

	auto topo = std::make_shared<Geo2d_TopoChainAnalysis>();
	Debug_Null_Pointer(topo);

	topo->Import(*merged);
	topo->Perform();
	topo->reReisterEdges();

	const auto& echains = topo->Edges();
	if (echains.size() NOT_EQUAL theCurves.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "- Something goes wrong!" << endl
			<< " - echains size = " << (label)echains.size() << endl
			<< " - curves size = " << (label)theCurves.size() << endl
			<< abort(FatalError);
	}

	for (size_t i = 0; i < echains.size(); i++)
	{
		auto paired = std::make_pair(echains[i], curves[i]);
		auto insert = theEdges.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been detected!" << endl
				<< abort(FatalError);
		}
	}

	topo->ClearEdges();

	return std::move(topo);
}