#include <HydStatic_BonjeanGraph.hxx>

tnbLib::HydStatic_BonjeanGraph::GraphSect::GraphSect
(
	const std::shared_ptr<Marine_CmpSection>& theSection,
	std::vector<std::shared_ptr<HydStatic_BnjCurve>>&& theCurves
)
	: theSection_(theSection)
	, theCurves_(std::move(theCurves))
{
	// empty body [6/3/2021 Amir]
}

tnbLib::HydStatic_BonjeanGraph::GraphSect::GraphSect
(
	const std::shared_ptr<Marine_CmpSection>& theSection, 
	const std::vector<std::shared_ptr<HydStatic_BnjCurve>>& theCurves
)
	: theSection_(theSection)
	, theCurves_(theCurves)
{
	// empty body [6/16/2021 Amir]
}

tnbLib::HydStatic_BonjeanGraph::HydStatic_BonjeanGraph
(
	std::vector<std::shared_ptr<GraphSect>>&& theSections
)
	: theSections_(std::move(theSections))
{
	// empty body [6/3/2021 Amir]
}