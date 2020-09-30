#include <Marine_Domain.hxx>

namespace tnbLib
{
	const Standard_Real Marine_Domain::DEFAULT_EXPAND_COEFF(2.5);
}

tnbLib::Marine_Domain::Marine_Domain()
	: Marine_CoordinatedEntity(0, "domain")
{
	theDomain_ = std::make_shared<Entity3d_Box>();
}

tnbLib::Marine_Domain::Marine_Domain
(
	const Standard_Integer theIndex
)
	: Marine_CoordinatedEntity(theIndex, "domain")
{
	theDomain_ = std::make_shared<Entity3d_Box>();
}

tnbLib::Marine_Domain::Marine_Domain
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_CoordinatedEntity(theIndex, theName)
{
	theDomain_ = std::make_shared<Entity3d_Box>();
}

#include <Entity2d_Box.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>
#include <MarineBase_Tools.hxx>

void tnbLib::Marine_Domain::Perform
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel
)
{

	auto domain = MarineBase_Tools::CalcBoundingBox(theModel);
	Perform(domain);
}

void tnbLib::Marine_Domain::Perform
(
	const Entity3d_Box & domain
)
{
	auto[dx, dy, dz] = domain.Length();
	*ChangeDim() = domain.Expanded(dx*ExpandCoeff(), dy*ExpandCoeff(), dz*ExpandCoeff());
	Change_IsDone() = Standard_True;
}