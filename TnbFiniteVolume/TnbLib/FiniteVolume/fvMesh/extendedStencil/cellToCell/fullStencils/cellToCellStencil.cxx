#include <cellToCellStencil.hxx>

#include <faceList.hxx>
#include <syncTools.hxx>
#include <SortableList.hxx>
#include <IndirectList.hxx>
#include <labelList.hxx>
#include <polyMesh.hxx>
#include <indirectPrimitivePatch.hxx>

#include <emptyPolyPatch.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Merge two list and guarantee global0,global1 are first.
void tnbLib::cellToCellStencil::merge
(
	const label global0,
	const label global1,
	const labelList& listA,
	labelList& listB
)
{
	sort(listB);

	// See if global0, global1 already present in listB
	label nGlobalInsert = 0;

	if (global0 != -1)
	{
		label index0 = findSortedIndex(listB, global0);
		if (index0 == -1)
		{
			nGlobalInsert++;
		}
	}

	if (global1 != -1)
	{
		label index1 = findSortedIndex(listB, global1);
		if (index1 == -1)
		{
			nGlobalInsert++;
		}
	}


	// For all in listA see if they are present
	label nInsert = 0;

	forAll(listA, i)
	{
		label elem = listA[i];

		if (elem != global0 && elem != global1)
		{
			if (findSortedIndex(listB, elem) == -1)
			{
				nInsert++;
			}
		}
	}

	// Extend B with nInsert and whether global0,global1 need to be inserted.
	labelList result(listB.size() + nGlobalInsert + nInsert);

	label resultI = 0;

	// Insert global0,1 first
	if (global0 != -1)
	{
		result[resultI++] = global0;
	}
	if (global1 != -1)
	{
		result[resultI++] = global1;
	}


	// Insert listB
	forAll(listB, i)
	{
		label elem = listB[i];

		if (elem != global0 && elem != global1)
		{
			result[resultI++] = elem;
		}
	}


	// Insert listA
	forAll(listA, i)
	{
		label elem = listA[i];

		if (elem != global0 && elem != global1)
		{
			if (findSortedIndex(listB, elem) == -1)
			{
				result[resultI++] = elem;
			}
		}
	}

	if (resultI != result.size())
	{
		FatalErrorIn("cellToCellStencil::merge(..)")
			<< "problem" << abort(FatalError);
	}

	listB.transfer(result);
}


// Merge two list and guarantee globalI is first.
void tnbLib::cellToCellStencil::merge
(
	const label globalI,
	const labelList& pGlobals,
	labelList& cCells
)
{
	labelHashSet set;
	forAll(cCells, i)
	{
		if (cCells[i] != globalI)
		{
			set.insert(cCells[i]);
		}
	}

	forAll(pGlobals, i)
	{
		if (pGlobals[i] != globalI)
		{
			set.insert(pGlobals[i]);
		}
	}

	cCells.setSize(set.size() + 1);
	label n = 0;
	cCells[n++] = globalI;

	forAllConstIter(labelHashSet, set, iter)
	{
		cCells[n++] = iter.key();
	}
}


void tnbLib::cellToCellStencil::validBoundaryFaces(boolList& isValidBFace) const
{
	const polyBoundaryMesh& patches = mesh().boundaryMesh();

	isValidBFace.setSize(mesh().nFaces() - mesh().nInternalFaces(), true);

	forAll(patches, patchI)
	{
		const polyPatch& pp = patches[patchI];

		if (pp.coupled() || isA<emptyPolyPatch>(pp))
		{
			label bFaceI = pp.start() - mesh().nInternalFaces();
			forAll(pp, i)
			{
				isValidBFace[bFaceI++] = false;
			}
		}
	}
}


tnbLib::autoPtr<tnbLib::indirectPrimitivePatch>
tnbLib::cellToCellStencil::allCoupledFacesPatch() const
{
	const polyBoundaryMesh& patches = mesh().boundaryMesh();

	label nCoupled = 0;

	forAll(patches, patchI)
	{
		const polyPatch& pp = patches[patchI];

		if (pp.coupled())
		{
			nCoupled += pp.size();
		}
	}
	labelList coupledFaces(nCoupled);
	nCoupled = 0;

	forAll(patches, patchI)
	{
		const polyPatch& pp = patches[patchI];

		if (pp.coupled())
		{
			label faceI = pp.start();

			forAll(pp, i)
			{
				coupledFaces[nCoupled++] = faceI++;
			}
		}
	}

	return autoPtr<indirectPrimitivePatch>
		(
			new indirectPrimitivePatch
			(
				IndirectList<face>
				(
					mesh().faces(),
					coupledFaces
					),
				mesh().points()
			)
			);
}


void tnbLib::cellToCellStencil::unionEqOp::operator()
(
	labelList& x,
	const labelList& y
	) const
{
	if (y.size())
	{
		if (x.empty())
		{
			x = y;
		}
		else
		{
			labelHashSet set(x);
			forAll(y, i)
			{
				set.insert(y[i]);
			}
			x = set.toc();
		}
	}
}


void tnbLib::cellToCellStencil::insertFaceCells
(
	const label exclude0,
	const label exclude1,
	const boolList& isValidBFace,
	const labelList& faceLabels,
	labelHashSet& globals
) const
{
	const labelList& own = mesh().faceOwner();
	const labelList& nei = mesh().faceNeighbour();

	forAll(faceLabels, i)
	{
		label faceI = faceLabels[i];

		label globalOwn = globalNumbering().toGlobal(own[faceI]);
		if (globalOwn != exclude0 && globalOwn != exclude1)
		{
			globals.insert(globalOwn);
		}

		if (mesh().isInternalFace(faceI))
		{
			label globalNei = globalNumbering().toGlobal(nei[faceI]);
			if (globalNei != exclude0 && globalNei != exclude1)
			{
				globals.insert(globalNei);
			}
		}
		else
		{
			label bFaceI = faceI - mesh().nInternalFaces();

			if (isValidBFace[bFaceI])
			{
				label globalI = globalNumbering().toGlobal
				(
					mesh().nCells()
					+ bFaceI
				);

				if (globalI != exclude0 && globalI != exclude1)
				{
					globals.insert(globalI);
				}
			}
		}
	}
}


tnbLib::labelList tnbLib::cellToCellStencil::calcFaceCells
(
	const boolList& isValidBFace,
	const labelList& faceLabels,
	labelHashSet& globals
) const
{
	globals.clear();

	insertFaceCells
	(
		-1,
		-1,
		isValidBFace,
		faceLabels,
		globals
	);

	return globals.toc();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellToCellStencil::cellToCellStencil(const polyMesh& mesh)
	:
	mesh_(mesh),
	globalNumbering_(mesh_.nCells() + mesh_.nFaces() - mesh_.nInternalFaces())
{}


// ************************************************************************* //