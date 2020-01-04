#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcCellCells() const
{
	// Loop through faceCells and mark up neighbours

	if (debug)
	{
		Pout << "primitiveMesh::calcCellCells() : calculating cellCells"
			<< endl;

		if (debug == -1)
		{
			// For checking calls:abort so we can quickly hunt down
			// origin of call
			FatalErrorIn("primitiveMesh::calcCellCells()")
				<< abort(FatalError);
		}
	}

	// It is an error to attempt to recalculate cellCells
	// if the pointer is already set
	if (ccPtr_)
	{
		FatalErrorIn("primitiveMesh::calcCellCells() const")
			<< "cellCells already calculated"
			<< abort(FatalError);
	}
	else
	{
		// 1. Count number of internal faces per cell

		labelList ncc(nCells(), 0);

		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();

		forAll(nei, faceI)
		{
			ncc[own[faceI]]++;
			ncc[nei[faceI]]++;
		}

		// Create the storage
		ccPtr_ = new labelListList(ncc.size());
		labelListList& cellCellAddr = *ccPtr_;



		// 2. Size and fill cellCellAddr

		forAll(cellCellAddr, cellI)
		{
			cellCellAddr[cellI].setSize(ncc[cellI]);
		}
		ncc = 0;

		forAll(nei, faceI)
		{
			label ownCellI = own[faceI];
			label neiCellI = nei[faceI];

			cellCellAddr[ownCellI][ncc[ownCellI]++] = neiCellI;
			cellCellAddr[neiCellI][ncc[neiCellI]++] = ownCellI;
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::cellCells() const
{
	if (!ccPtr_)
	{
		calcCellCells();
	}

	return *ccPtr_;
}


const tnbLib::labelList& tnbLib::primitiveMesh::cellCells
(
	const label cellI,
	dynamicLabelList& storage
) const
{
	if (hasCellCells())
	{
		return cellCells()[cellI];
	}
	else
	{
		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();
		const cell& cFaces = cells()[cellI];

		storage.clear();

		forAll(cFaces, i)
		{
			label faceI = cFaces[i];

			if (faceI < nInternalFaces())
			{
				if (own[faceI] == cellI)
				{
					storage.append(nei[faceI]);
				}
				else
				{
					storage.append(own[faceI]);
				}
			}
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::cellCells(const label cellI) const
{
	return cellCells(cellI, labels_);
}


// ************************************************************************* //