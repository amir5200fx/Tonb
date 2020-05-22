#include <CPCCellToCellStencil.hxx>

#include <syncTools.hxx>
#include <polyMesh.hxx>


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Calculates per point the neighbour data (= pointCells)
void tnbLib::CPCCellToCellStencil::calcPointBoundaryData
(
	const boolList& isValidBFace,
	const labelList& boundaryPoints,
	Map<labelList>& neiGlobal
) const
{
	neiGlobal.resize(2 * boundaryPoints.size());

	labelHashSet pointGlobals;

	forAll(boundaryPoints, i)
	{
		label pointI = boundaryPoints[i];

		neiGlobal.insert
		(
			pointI,
			calcFaceCells
			(
				isValidBFace,
				mesh().pointFaces()[pointI],
				pointGlobals
			)
		);
	}

	syncTools::syncPointMap
	(
		mesh(),
		neiGlobal,
		unionEqOp(),
		false           // apply separation
	);
}


// Calculates per cell the neighbour data (= cell or boundary in global
// numbering). First element is always cell itself!
void tnbLib::CPCCellToCellStencil::calcCellStencil
(
	labelListList& globalCellCells
) const
{
	// Calculate points on coupled patches
	labelList boundaryPoints(allCoupledFacesPatch()().meshPoints());


	// Mark boundary faces to be included in stencil (i.e. not coupled or empty)
	boolList isValidBFace;
	validBoundaryFaces(isValidBFace);


	// Swap pointCells for coupled points
	Map<labelList> neiGlobal;
	calcPointBoundaryData
	(
		isValidBFace,
		boundaryPoints,
		neiGlobal
	);

	globalCellCells.setSize(mesh().nCells());

	// Do coupled points first

	forAll(boundaryPoints, i)
	{
		label pointI = boundaryPoints[i];

		const labelList& pGlobals = neiGlobal[pointI];

		// Distribute to all pointCells
		const labelList& pCells = mesh().pointCells(pointI);

		forAll(pCells, j)
		{
			label cellI = pCells[j];

			// Insert pGlobals into globalCellCells
			merge
			(
				globalNumbering().toGlobal(cellI),
				pGlobals,
				globalCellCells[cellI]
			);
		}
	}
	neiGlobal.clear();

	// Do remaining points cells
	labelHashSet pointGlobals;

	for (label pointI = 0; pointI < mesh().nPoints(); pointI++)
	{
		labelList pGlobals
		(
			calcFaceCells
			(
				isValidBFace,
				mesh().pointFaces()[pointI],
				pointGlobals
			)
		);

		const labelList& pCells = mesh().pointCells(pointI);

		forAll(pCells, j)
		{
			label cellI = pCells[j];

			merge
			(
				globalNumbering().toGlobal(cellI),
				pGlobals,
				globalCellCells[cellI]
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CPCCellToCellStencil::CPCCellToCellStencil(const polyMesh& mesh)
	:
	cellToCellStencil(mesh)
{
	// Calculate per cell the (point) connected cells (in global numbering)
	labelListList globalCellCells;
	calcCellStencil(*this);
}


// ************************************************************************* //