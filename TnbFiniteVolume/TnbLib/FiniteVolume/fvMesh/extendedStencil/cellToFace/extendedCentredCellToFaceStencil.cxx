#include <extendedCentredCellToFaceStencil.hxx>

#include <mapDistribute.hxx>
#include <cellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedCentredCellToFaceStencil::extendedCentredCellToFaceStencil
(
	const cellToFaceStencil& stencil
)
	:
	extendedCellToFaceStencil(stencil.mesh())
{
	stencil_ = stencil;

	// Calculate distribute map (also renumbers elements in stencil)
	mapPtr_ = calcDistributeMap
	(
		stencil.mesh(),
		stencil.globalNumbering(),
		stencil_
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Per face which elements of the stencil to keep.
void tnbLib::extendedCentredCellToFaceStencil::compact()
{
	boolList isInStencil(map().constructSize(), false);

	forAll(stencil_, faceI)
	{
		const labelList& stencilCells = stencil_[faceI];

		forAll(stencilCells, i)
		{
			isInStencil[stencilCells[i]] = true;
		}
	}

	mapPtr_().compact(isInStencil);
}


// ************************************************************************* //