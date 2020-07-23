#include <Marine_Domain.hxx>

namespace tnbLib
{
	const Standard_Real Marine_Domain::DEFAULT_EXPAND_COEFF(2.5);
}

tnbLib::Marine_Domain::Marine_Domain()
	: Marine_CoordinatedEntity(0, "domain")
{
}

tnbLib::Marine_Domain::Marine_Domain
(
	const Standard_Integer theIndex
)
	: Marine_CoordinatedEntity(theIndex, "domain")
{
}

tnbLib::Marine_Domain::Marine_Domain
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_CoordinatedEntity(theIndex, theName)
{
}

#include <Entity2d_Box.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>

void tnbLib::Marine_Domain::Perform
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel
)
{
	auto iter = theModel.begin();
	auto b = (*iter)->BoundingBox();

	iter++;
	while (iter NOT_EQUAL theModel.end())
	{
		b = Entity2d_Box::Union(b, (*iter)->BoundingBox());
		iter++;
	}

	const auto x0 = theModel[0]->X();
	const auto x1 = theModel[theModel.size() - 1]->X();

	const auto y0 = b.P0().X();
	const auto y1 = b.P1().X();

	const auto z0 = b.P0().Y();
	const auto z1 = b.P1().Y();

	auto domain = Entity3d_Box(Pnt3d(x0, y0, z0), Pnt3d(x1, y1, z1));

	Perform(domain);
}

void tnbLib::Marine_Domain::Perform
(
	const Entity3d_Box & domain
)
{
	auto[dx, dy, dz] = domain.Length();
	ChangeDim() = domain.Expanded(dx*ExpandCoeff(), dy*ExpandCoeff(), dz*ExpandCoeff());
	Change_IsDone() = Standard_True;
}