#include <primitiveMesh.hxx>

#include <cell.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcPointCells() const
{
	// Loop through cells and mark up points

	if (debug)
	{
		Pout << "primitiveMesh::calcPointCells() : "
			<< "calculating pointCells"
			<< endl;

		if (debug == -1)
		{
			// For checking calls:abort so we can quickly hunt down
			// origin of call
			FatalErrorIn("primitiveMesh::calcPointCells()")
				<< abort(FatalError);
		}
	}

	// It is an error to attempt to recalculate pointCells
	// if the pointer is already set
	if (pcPtr_)
	{
		FatalErrorIn("primitiveMesh::calcPointCells() const")
			<< "pointCells already calculated"
			<< abort(FatalError);
	}
	else
	{
		const cellList& cf = cells();

		// Count number of cells per point

		labelList npc(nPoints(), 0);

		forAll(cf, cellI)
		{
			const labelList curPoints = cf[cellI].labels(faces());

			forAll(curPoints, pointI)
			{
				label ptI = curPoints[pointI];

				npc[ptI]++;
			}
		}


		// Size and fill cells per point

		pcPtr_ = new labelListList(npc.size());
		labelListList& pointCellAddr = *pcPtr_;

		forAll(pointCellAddr, pointI)
		{
			pointCellAddr[pointI].setSize(npc[pointI]);
		}
		npc = 0;


		forAll(cf, cellI)
		{
			const labelList curPoints = cf[cellI].labels(faces());

			forAll(curPoints, pointI)
			{
				label ptI = curPoints[pointI];

				pointCellAddr[ptI][npc[ptI]++] = cellI;
			}
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::pointCells() const
{
	if (!pcPtr_)
	{
		calcPointCells();
	}

	return *pcPtr_;
}


const tnbLib::labelList& tnbLib::primitiveMesh::pointCells
(
	const label pointI,
	dynamicLabelList& storage
) const
{
	if (hasPointCells())
	{
		return pointCells()[pointI];
	}
	else
	{
		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();
		const labelList& pFaces = pointFaces()[pointI];

		storage.clear();

		forAll(pFaces, i)
		{
			const label faceI = pFaces[i];

			// Append owner
			storage.append(own[faceI]);

			// Append neighbour
			if (faceI < nInternalFaces())
			{
				storage.append(nei[faceI]);
			}
		}

		// Filter duplicates
		if (storage.size() > 1)
		{
			sort(storage);

			label n = 1;
			for (label i = 1; i < storage.size(); i++)
			{
				if (storage[i - 1] != storage[i])
				{
					storage[n++] = storage[i];
				}
			}

			// truncate addressed list
			storage.setSize(n);
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::pointCells(const label pointI) const
{
	return pointCells(pointI, labels_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //