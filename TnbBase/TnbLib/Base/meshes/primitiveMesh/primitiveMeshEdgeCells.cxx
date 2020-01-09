#include <primitiveMesh.hxx>

#include <ListOps.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::edgeCells() const
{
	if (!ecPtr_)
	{
		if (debug)
		{
			Pout << "primitiveMesh::edgeCells() : calculating edgeCells"
				<< endl;

			if (debug == -1)
			{
				// For checking calls:abort so we can quickly hunt down
				// origin of call
				FatalErrorIn("primitiveMesh::edgeCells()")
					<< abort(FatalError);
			}
		}
		// Invert cellEdges
		ecPtr_ = new labelListList(nEdges());
		invertManyToMany(nEdges(), cellEdges(), *ecPtr_);
	}

	return *ecPtr_;
}


const tnbLib::labelList& tnbLib::primitiveMesh::edgeCells
(
	const label edgeI,
	dynamicLabelList& storage
) const
{
	if (hasEdgeCells())
	{
		return edgeCells()[edgeI];
	}
	else
	{
		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();

		// Construct edgeFaces
		dynamicLabelList eFacesStorage;
		const labelList& eFaces = edgeFaces(edgeI, eFacesStorage);

		storage.clear();

		// Do quadratic insertion.
		forAll(eFaces, i)
		{
			label faceI = eFaces[i];

			{
				label ownCellI = own[faceI];

				// Check if not already in storage
				forAll(storage, j)
				{
					if (storage[j] == ownCellI)
					{
						ownCellI = -1;
						break;
					}
				}

				if (ownCellI != -1)
				{
					storage.append(ownCellI);
				}
			}

			if (isInternalFace(faceI))
			{
				label neiCellI = nei[faceI];

				forAll(storage, j)
				{
					if (storage[j] == neiCellI)
					{
						neiCellI = -1;
						break;
					}
				}

				if (neiCellI != -1)
				{
					storage.append(neiCellI);
				}
			}
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::edgeCells(const label edgeI) const
{
	return edgeCells(edgeI, labels_);
}


// ************************************************************************* //