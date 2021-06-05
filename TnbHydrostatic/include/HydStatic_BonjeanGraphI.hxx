#pragma once
inline Standard_Integer 
tnbLib::HydStatic_BonjeanGraph::GraphSect::NbSections() const
{
	return (Standard_Integer)theCurves_.size();
}

inline void tnbLib::HydStatic_BonjeanGraph::GraphSect::SetSection
(
	const std::shared_ptr<Marine_CmpSection>& theSect
)
{
	theSection_ = theSect;
}

inline void tnbLib::HydStatic_BonjeanGraph::GraphSect::SetCurves
(
	std::vector<std::shared_ptr<HydStatic_BnjCurve>>&& theCurves
)
{
	theCurves_ = std::move(theCurves);
}

inline void tnbLib::HydStatic_BonjeanGraph::GraphSect::SetCurves
(
	const std::vector<std::shared_ptr<HydStatic_BnjCurve>>& theCurves
)
{
	theCurves_ = theCurves;
}

inline Standard_Integer 
tnbLib::HydStatic_BonjeanGraph::NbSections() const
{
	return (Standard_Integer)theSections_.size();
}

inline void tnbLib::HydStatic_BonjeanGraph::SetSections
(
	std::vector<std::shared_ptr<GraphSect>>&& theSections
)
{
	theSections_ = std::move(theSections);
}