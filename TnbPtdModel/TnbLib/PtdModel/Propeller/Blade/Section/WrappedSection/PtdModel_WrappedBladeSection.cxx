#include <PtdModel_WrappedBladeSection.hxx>

tnbLib::PtdModel_WrappedBladeSection::PtdModel_WrappedBladeSection
(
	const std::vector<Pnt3d>& theFace, 
	const std::vector<Pnt3d>& theBack
)
	: PtdModel_BladeSection(theFace, theBack)
{
	//- empty body
}

tnbLib::PtdModel_WrappedBladeSection::PtdModel_WrappedBladeSection
(
	std::vector<Pnt3d>&& theFace,
	std::vector<Pnt3d>&& theBack
)
	: PtdModel_BladeSection(std::move(theFace), std::move(theBack))
{
	//- empty body
}