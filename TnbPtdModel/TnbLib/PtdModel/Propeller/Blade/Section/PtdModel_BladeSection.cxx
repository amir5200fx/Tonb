#include <PtdModel_BladeSection.hxx>

tnbLib::PtdModel_BladeSection::PtdModel_BladeSection
(
	const std::vector<Pnt3d>& theFace, 
	const std::vector<Pnt3d>& theBack
)
	: theFace_(theFace)
	, theBack_(theBack)
{
	//- empty body
}

tnbLib::PtdModel_BladeSection::PtdModel_BladeSection
(
	std::vector<Pnt3d>&& theFace, 
	std::vector<Pnt3d>&& theBack
)
	: theFace_(std::move(theFace))
	, theBack_(std::move(theBack))
{
	//- empty body
}