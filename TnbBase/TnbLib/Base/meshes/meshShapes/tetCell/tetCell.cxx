#include <tetCell.hxx>
#include <cellShape.hxx>
#include <cellModeller.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::cellShape tnbLib::tetCell::tetCellShape() const
{
	static const cellModel* tetModelPtr_ = NULL;

	if (!tetModelPtr_)
	{
		tetModelPtr_ = cellModeller::lookup("tet");
	}

	const cellModel& tet = *tetModelPtr_;

	return cellShape(tet, *this);
}


// ************************************************************************* //
