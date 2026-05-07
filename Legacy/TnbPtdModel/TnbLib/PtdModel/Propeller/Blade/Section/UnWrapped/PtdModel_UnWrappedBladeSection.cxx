#include <PtdModel_UnWrappedBladeSection.hxx>

tnbLib::PtdModel_UnWrappedBladeSection::PtdModel_UnWrappedBladeSection
(
	const std::vector<Pnt3d>& theFace,
	const std::vector<Pnt3d>& theBack
)
	: PtdModel_BladeSection(theFace, theBack)
{
	//- empty body
}

tnbLib::PtdModel_UnWrappedBladeSection::PtdModel_UnWrappedBladeSection
(
	std::vector<Pnt3d>&& theFace,
	std::vector<Pnt3d>&& theBack
)
	: PtdModel_BladeSection(std::move(theFace), std::move(theBack))
{
	//- empty body
}