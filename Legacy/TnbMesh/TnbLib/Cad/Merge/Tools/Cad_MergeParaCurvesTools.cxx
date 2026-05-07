#include <Cad_MergeParaCurvesTools.hxx>

#include <Cad_MergeParaCurves_InternalNode.hxx>
#include <Cad_MergeParaCurves_Node.hxx>
#include <Cad_MergeParaCurves_Link.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::cadLib::mergeParaCurves::Node>> 
tnbLib::Cad_MergeParaCurvesTools::RetrieveNodes
(
	const std::vector<std::shared_ptr<cadLib::mergeParaCurves::Link>>& theCurves
)
{
	std::map<Standard_Integer, std::shared_ptr<cadLib::mergeParaCurves::Node>> nodeMap;
	for (const auto& x : theCurves)
	{
		auto[n0, n1] = x->RetrieveNodes();
		Debug_Null_Pointer(n0);

		Global_Tools::InsertIgnoreDup(n0->Index(), std::move(n0), nodeMap);
		if (n1)
		{
			Global_Tools::InsertIgnoreDup(n1->Index(), std::move(n1), nodeMap);
		}
	}
	std::vector<std::shared_ptr<cadLib::mergeParaCurves::Node>> nodes;
	nodes.reserve(nodeMap.size());
	for (auto& x : nodeMap)
	{
		Debug_Null_Pointer(x.second);
		auto& node = x.second;
		nodes.push_back(std::move(node));
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::cadLib::mergeParaCurves::Node>> 
tnbLib::Cad_MergeParaCurvesTools::RetrieveIntsctNodes
(
	const std::vector<std::shared_ptr<cadLib::mergeParaCurves::Node>>& theNodes
)
{

	std::vector<std::shared_ptr<cadLib::mergeParaCurves::Node>> nodes;
	for (const auto& x : theNodes)
	{
		if (x->IsIntersection())
		{
			nodes.push_back(x);
		}
	}
	return std::move(nodes);
}