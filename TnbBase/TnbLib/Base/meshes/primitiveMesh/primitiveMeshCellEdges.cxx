#include <primitiveMesh.hxx>

#include <DynamicList.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::primitiveMesh::calcCellEdges() const
{
	// Loop through all faces and mark up cells with edges of the face.
	// Check for duplicates

	if (debug)
	{
		Pout << "primitiveMesh::calcCellEdges() : "
			<< "calculating cellEdges"
			<< endl;

		if (debug == -1)
		{
			// For checking calls:abort so we can quickly hunt down
			// origin of call
			FatalErrorIn("primitiveMesh::calcCellEdges()")
				<< abort(FatalError);
		}
	}

	// It is an error to attempt to recalculate cellEdges
	// if the pointer is already set
	if (cePtr_)
	{
		FatalErrorIn("primitiveMesh::calcCellEdges() const")
			<< "cellEdges already calculated"
			<< abort(FatalError);
	}
	else
	{
		// Set up temporary storage
		List<DynamicList<label, edgesPerCell_> > ce(nCells());


		// Get reference to faceCells and faceEdges
		const labelList& own = faceOwner();
		const labelList& nei = faceNeighbour();
		const labelListList& fe = faceEdges();

		// loop through the list again and add edges; checking for duplicates
		forAll(own, faceI)
		{
			DynamicList<label, edgesPerCell_>& curCellEdges = ce[own[faceI]];

			const labelList& curEdges = fe[faceI];

			forAll(curEdges, edgeI)
			{
				if (findIndex(curCellEdges, curEdges[edgeI]) == -1)
				{
					// Add the edge
					curCellEdges.append(curEdges[edgeI]);
				}
			}
		}

		forAll(nei, faceI)
		{
			DynamicList<label, edgesPerCell_>& curCellEdges = ce[nei[faceI]];

			const labelList& curEdges = fe[faceI];

			forAll(curEdges, edgeI)
			{
				if (findIndex(curCellEdges, curEdges[edgeI]) == -1)
				{
					// add the edge
					curCellEdges.append(curEdges[edgeI]);
				}
			}
		}

		cePtr_ = new labelListList(ce.size());
		labelListList& cellEdgeAddr = *cePtr_;

		// reset the size
		forAll(ce, cellI)
		{
			cellEdgeAddr[cellI].transfer(ce[cellI]);
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList& tnbLib::primitiveMesh::cellEdges() const
{
	if (!cePtr_)
	{
		calcCellEdges();
	}

	return *cePtr_;
}


// ************************************************************************* //