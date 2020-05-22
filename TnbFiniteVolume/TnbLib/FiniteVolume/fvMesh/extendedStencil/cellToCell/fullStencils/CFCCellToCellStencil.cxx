#include <CFCCellToCellStencil.hxx>

#include <syncTools.hxx>
#include <SortableList.hxx>
#include <emptyPolyPatch.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Calculates per face the neighbour data (= cell or boundary face)
void tnbLib::CFCCellToCellStencil::calcFaceBoundaryData
(
	labelList& neiGlobal
) const
{
	const polyBoundaryMesh& patches = mesh().boundaryMesh();
	const label nBnd = mesh().nFaces() - mesh().nInternalFaces();
	const labelList& own = mesh().faceOwner();

	neiGlobal.setSize(nBnd);

	forAll(patches, patchI)
	{
		const polyPatch& pp = patches[patchI];
		label faceI = pp.start();

		if (pp.coupled())
		{
			// For coupled faces get the cell on the other side
			forAll(pp, i)
			{
				label bFaceI = faceI - mesh().nInternalFaces();
				neiGlobal[bFaceI] = globalNumbering().toGlobal(own[faceI]);
				faceI++;
			}
		}
		else if (isA<emptyPolyPatch>(pp))
		{
			forAll(pp, i)
			{
				label bFaceI = faceI - mesh().nInternalFaces();
				neiGlobal[bFaceI] = -1;
				faceI++;
			}
		}
		else
		{
			// For noncoupled faces get the boundary face.
			forAll(pp, i)
			{
				label bFaceI = faceI - mesh().nInternalFaces();
				neiGlobal[bFaceI] =
					globalNumbering().toGlobal(mesh().nCells() + bFaceI);
				faceI++;
			}
		}
	}
	syncTools::swapBoundaryFaceList(mesh(), neiGlobal, false);
}


// Calculates per cell the neighbour data (= cell or boundary in global
// numbering). First element is always cell itself!
void tnbLib::CFCCellToCellStencil::calcCellStencil(labelListList& globalCellCells)
const
{
	const label nBnd = mesh().nFaces() - mesh().nInternalFaces();
	const labelList& own = mesh().faceOwner();
	const labelList& nei = mesh().faceNeighbour();


	// Calculate coupled neighbour (in global numbering)
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	labelList neiGlobal(nBnd);
	calcFaceBoundaryData(neiGlobal);


	// Determine cellCells in global numbering
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	globalCellCells.setSize(mesh().nCells());
	forAll(globalCellCells, cellI)
	{
		const cell& cFaces = mesh().cells()[cellI];

		labelList& cCells = globalCellCells[cellI];

		cCells.setSize(cFaces.size() + 1);

		label nNbr = 0;

		// Myself
		cCells[nNbr++] = globalNumbering().toGlobal(cellI);

		// Collect neighbouring cells/faces
		forAll(cFaces, i)
		{
			label faceI = cFaces[i];

			if (mesh().isInternalFace(faceI))
			{
				label nbrCellI = own[faceI];
				if (nbrCellI == cellI)
				{
					nbrCellI = nei[faceI];
				}
				cCells[nNbr++] = globalNumbering().toGlobal(nbrCellI);
			}
			else
			{
				label nbrCellI = neiGlobal[faceI - mesh().nInternalFaces()];
				if (nbrCellI != -1)
				{
					cCells[nNbr++] = nbrCellI;
				}
			}
		}
		cCells.setSize(nNbr);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CFCCellToCellStencil::CFCCellToCellStencil(const polyMesh& mesh)
	:
	cellToCellStencil(mesh)
{
	// Calculate per cell the (face) connected cells (in global numbering)
	calcCellStencil(*this);
}


// ************************************************************************* //