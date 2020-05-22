#include <extendedCentredFaceToCellStencil.hxx>

#include <mapDistribute.hxx>
#include <faceToCellStencil.hxx>

// Only for access to calcDistributeMap <- needs to be moved out
#include <extendedCellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedCentredFaceToCellStencil::extendedCentredFaceToCellStencil
(
	const faceToCellStencil& stencil
)
	:
	extendedFaceToCellStencil(stencil.mesh())
{
	stencil_ = stencil;

	// Calculate distribute map (also renumbers elements in stencil)
	mapPtr_ = extendedCellToFaceStencil::calcDistributeMap
	(
		stencil.mesh(),
		stencil.globalNumbering(),
		stencil_
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Per face which elements of the stencil to keep.
void tnbLib::extendedCentredFaceToCellStencil::compact()
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