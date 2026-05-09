#include <PtdModel_BladeSection.hxx>

tnbLib::PtdModel_BladeSection::PtdModel_BladeSection
(
	const std::vector<Pnt3d>& theFace, 
	const std::vector<Pnt3d>& theBack
)
{
	base::faceQ f(theFace);
	base::backQ b(theBack);

	SetQ(std::move(f));
	SetQ(std::move(b));
}

tnbLib::PtdModel_BladeSection::PtdModel_BladeSection
(
	std::vector<Pnt3d>&& theFace, 
	std::vector<Pnt3d>&& theBack
)
{
	base::faceQ f(std::move(theFace));
	base::backQ b(std::move(theBack));

	SetQ(std::move(f));
	SetQ(std::move(b));
}