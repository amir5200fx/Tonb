#include <bandCompression.hxx>

#include <SLList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Constructor from components
tnbLib::labelList tnbLib::bandCompression(const labelListList& cellCellAddressing)
{
	labelList newOrder(cellCellAddressing.size());

	// the business bit of the renumbering
	SLList<label> nextCell;

	labelList visited(cellCellAddressing.size());

	label currentCell;
	label cellInOrder = 0;

	// reset the visited cells list
	forAll(visited, cellI)
	{
		visited[cellI] = 0;
	}

	// loop over the cells
	forAll(visited, cellI)
	{
		// find the first cell that has not been visited yet
		if (visited[cellI] == 0)
		{
			currentCell = cellI;

			// use this cell as a start
			nextCell.append(currentCell);

			// loop through the nextCell list. Add the first cell into the
			// cell order if it has not already been visited and ask for its
			// neighbours. If the neighbour in question has not been visited,
			// add it to the end of the nextCell list

			while (nextCell.size())
			{
				currentCell = nextCell.removeHead();

				if (visited[currentCell] == 0)
				{
					visited[currentCell] = 1;

					// add into cellOrder
					newOrder[cellInOrder] = currentCell;
					cellInOrder++;

					// find if the neighbours have been visited
					const labelList& neighbours =
						cellCellAddressing[currentCell];

					forAll(neighbours, nI)
					{
						if (visited[neighbours[nI]] == 0)
						{
							// not visited, add to the list
							nextCell.append(neighbours[nI]);
						}
					}
				}
			}
		}
	}

	return newOrder;
}


// ************************************************************************* //