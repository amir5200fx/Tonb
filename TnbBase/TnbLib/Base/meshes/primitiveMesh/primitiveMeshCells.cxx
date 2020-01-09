#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcCells
(
	cellList& cellFaceAddr,
	const unallocLabelList& own,
	const unallocLabelList& nei,
	const label inNCells
)
{
	label nCells = inNCells;

	if (nCells == -1)
	{
		nCells = -1;

		forAll(own, faceI)
		{
			nCells = max(nCells, own[faceI]);
		}
		nCells++;
	}

	// 1. Count number of faces per cell

	labelList ncf(nCells, 0);

	forAll(own, faceI)
	{
		ncf[own[faceI]]++;
	}

	forAll(nei, faceI)
	{
		if (nei[faceI] >= 0)
		{
			ncf[nei[faceI]]++;
		}
	}

	// Create the storage
	cellFaceAddr.setSize(ncf.size());


	// 2. Size and fill cellFaceAddr

	forAll(cellFaceAddr, cellI)
	{
		cellFaceAddr[cellI].setSize(ncf[cellI]);
	}
	ncf = 0;

	forAll(own, faceI)
	{
		label cellI = own[faceI];

		cellFaceAddr[cellI][ncf[cellI]++] = faceI;
	}

	forAll(nei, faceI)
	{
		label cellI = nei[faceI];

		if (cellI >= 0)
		{
			cellFaceAddr[cellI][ncf[cellI]++] = faceI;
		}
	}
}


void tnbLib::primitiveMesh::calcCells() const
{
	// Loop through faceCells and mark up neighbours

	if (debug)
	{
		Pout << "primitiveMesh::calcCells() : calculating cells"
			<< endl;
	}

	// It is an error to attempt to recalculate cells
	// if the pointer is already set
	if (cfPtr_)
	{
		FatalErrorIn("primitiveMesh::calcCells() const")
			<< "cells already calculated"
			<< abort(FatalError);
	}
	else
	{
		// Create the storage
		cfPtr_ = new cellList(nCells());
		cellList& cellFaceAddr = *cfPtr_;

		calcCells
		(
			cellFaceAddr,
			faceOwner(),
			faceNeighbour(),
			nCells()
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::cellList& tnbLib::primitiveMesh::cells() const
{
	if (!cfPtr_)
	{
		calcCells();
	}

	return *cfPtr_;
}


// ************************************************************************* //