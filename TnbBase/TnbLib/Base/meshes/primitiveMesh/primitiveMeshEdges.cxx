#include <primitiveMesh.hxx>

#include <DynamicList.hxx>
#include <demandDrivenData.hxx>
#include <SortableList.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Returns edgeI between two points.
tnbLib::label tnbLib::primitiveMesh::getEdge
(
	List<dynamicLabelList >& pe,
	DynamicList<edge>& es,

	const label pointI,
	const label nextPointI
)
{
	// Find connection between pointI and nextPointI
	forAll(pe[pointI], ppI)
	{
		label eI = pe[pointI][ppI];

		const edge& e = es[eI];

		if (e.start() == nextPointI || e.end() == nextPointI)
		{
			return eI;
		}
	}

	// Make new edge.
	label edgeI = es.size();
	pe[pointI].append(edgeI);
	pe[nextPointI].append(edgeI);
	if (pointI < nextPointI)
	{
		es.append(edge(pointI, nextPointI));
	}
	else
	{
		es.append(edge(nextPointI, pointI));
	}

	return edgeI;
}


void tnbLib::primitiveMesh::calcEdges() const
{
	if (debug)
	{
		Pout << "primitiveMesh::calcEdges() : "
			<< "calculating edges, pointEdges and faceEdges"
			<< endl;
	}

	// It is an error to attempt to recalculate edges
	// if the pointer is already set
	if (edgesPtr_ || fePtr_)
	{
		FatalErrorIn("primitiveMesh::calcEdges(const bool) const")
			<< "edges or faceEdges already calculated"
			<< abort(FatalError);
	}
	else
	{
		// Note: replaced with the original and correct algorithm
		// which preserved correct ordering for edges list
		// Version 1.5.x, 1.5-dev were wrong, with failures in parallel
		// point-based data exchange.  Fixed in 1.6-ext and
		// consecutive versions
		// HJ, 27/Aug/2010

		// ALGORITHM:
		// Go through the pointFace list.  Go through the list of faces for
		// that point and ask for edges.  If the edge has got the point
		// in question AND the second point in the edge is larger than
		// the first, add the edge to the list.  At the same time,
		// add the edge label to the listof edges for the current face
		// (faceEdges) and log the other face as the neighbour of this face.

		const faceList& f = faces();

		const labelListList& pf = pointFaces();

		fePtr_ = new labelListList(nFaces());
		labelListList& fe = *fePtr_;

		// count the maximum number of edges
		label maxEdges = 0;

		// create a list of edges for each face and store for efficiency
		edgeListList edgesOfFace(nFaces());

		forAll(f, faceI)
		{
			edgesOfFace[faceI] = f[faceI].edges();

			maxEdges += f[faceI].nEdges();

			labelList& curFE = fe[faceI];

			curFE.setSize(f[faceI].nEdges());

			forAll(curFE, curFEI)
			{
				curFE[curFEI] = -1;
			}
		}

		// EDGE CALCULATION

		edgesPtr_ = new edgeList(maxEdges);
		edgeList& e = *edgesPtr_;
		label nEdges = 0;

		forAll(pf, pointI)
		{
			const labelList& curFaces = pf[pointI];

			// create a list of labels to keep the neighbours that
			// have already been added
			DynamicList<label, edgesPerPoint_> addedNeighbours;
			DynamicList<DynamicList<label, edgesPerPoint_> >
				faceGivingNeighbour;
			DynamicList<DynamicList<label, edgesPerPoint_> >
				edgeOfFaceGivingNeighbour;

			forAll(curFaces, faceI)
			{
				// get the edges
				const edgeList& fEdges = edgesOfFace[curFaces[faceI]];

				// for every edge
				forAll(fEdges, edgeI)
				{
					const edge& ends = fEdges[edgeI];

					// does the edge has got the point in question
					bool found = false;
					label secondPoint = -1;

					if (ends.start() == pointI)
					{
						found = true;
						secondPoint = ends.end();
					}

					if (ends.end() == pointI)
					{
						found = true;
						secondPoint = ends.start();
					}

					// if the edge has got the point and second label is larger
					// than first, it is a candidate for adding
					if (found && (secondPoint > pointI))
					{
						// check if the edge has already been added
						bool added = false;

						forAll(addedNeighbours, eopI)
						{
							if (secondPoint == addedNeighbours[eopI])
							{
								// Edge is already added. New face sharing it
								added = true;

								// Remember the face and edge giving neighbour
								faceGivingNeighbour[eopI].append
								(curFaces[faceI]);

								edgeOfFaceGivingNeighbour[eopI].append(edgeI);

								break;
							}
						}

						// If not added, add the edge to the list
						if (!added)
						{
							addedNeighbours.append(secondPoint);

							// Remember the face and subShape giving neighbour
							faceGivingNeighbour(addedNeighbours.size() - 1)
								.append(curFaces[faceI]);
							edgeOfFaceGivingNeighbour
							(addedNeighbours.size() - 1).append(edgeI);
						}
					}
				}
			}

			// All edges for the current point found. Before adding them to the
			// list, it is necessary to sort them in the increasing order of
			// neighbouring point.

			// Make real list out of SLList to simplify the manipulation.
			// Also, make another list to "remember" how the original list was
			// reshuffled.
			labelList shuffleList(addedNeighbours.size());

			forAll(shuffleList, i)
			{
				shuffleList[i] = i;
			}

			// Use a simple sort to sort the addedNeighbours list.
			//  Other two lists mimic the same behaviour
			label i, j, a, b;

			for (j = 1; j <= addedNeighbours.size() - 1; j++)
			{
				a = addedNeighbours[j];
				b = shuffleList[j];

				i = j - 1;

				while (i >= 0 && addedNeighbours[i] > a)
				{
					addedNeighbours[i + 1] = addedNeighbours[i];
					shuffleList[i + 1] = shuffleList[i];
					i--;
				}

				addedNeighbours[i + 1] = a;
				shuffleList[i + 1] = b;
			}

			labelList reshuffleList(shuffleList.size());

			forAll(shuffleList, i)
			{
				reshuffleList[shuffleList[i]] = i;
			}

			// Reshuffle other lists

			labelListList fgn(faceGivingNeighbour.size());

			forAll(faceGivingNeighbour, i)
			{
				fgn[reshuffleList[i]].transfer
				(
					faceGivingNeighbour[i].shrink()
				);
			}

			labelListList eofgn(edgeOfFaceGivingNeighbour.size());

			forAll(edgeOfFaceGivingNeighbour, i)
			{
				eofgn[reshuffleList[i]].transfer
				(
					edgeOfFaceGivingNeighbour[i].shrink()
				);
			}

			// adding the edges
			forAll(addedNeighbours, edgeI)
			{
				const labelList& curFgn = fgn[edgeI];
				const labelList& curEofgn = eofgn[edgeI];

				forAll(curFgn, fgnI)
				{
					fe[curFgn[fgnI]][curEofgn[fgnI]] = nEdges;
				}

				e[nEdges] = edge(pointI, addedNeighbours[edgeI]);
				nEdges++;
			}
		}

		// reset the size
		e.setSize(nEdges);
	}
}

// Removed ordered edges: reverting to correct parallelisation
// of edge data.  HJ, 17/Aug/2010
// void primitiveMesh::calcOrderedEdges() const


tnbLib::label tnbLib::primitiveMesh::findFirstCommonElementFromSortedLists
(
	const labelList& list1,
	const labelList& list2
)
{
	label result = -1;

	labelList::const_iterator iter1 = list1.begin();
	labelList::const_iterator iter2 = list2.begin();

	while (iter1 != list1.end() && iter2 != list2.end())
	{
		if (*iter1 < *iter2)
		{
			++iter1;
		}
		else if (*iter1 > *iter2)
		{
			++iter2;
		}
		else
		{
			result = *iter1;
			break;
		}
	}
	if (result == -1)
	{
		FatalErrorIn
		(
			"primitiveMesh::findFirstCommonElementFromSortedLists"
			"(const labelList&, const labelList&)"
		) << "No common elements in lists " << list1 << " and " << list2
			<< abort(FatalError);
	}
	return result;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::edgeList& tnbLib::primitiveMesh::edges() const
{
	if (!edgesPtr_)
	{
		// 1.6.x merge: reverting to correct code
		// HJ, 17/Aug/2010
		calcEdges();
	}

	return *edgesPtr_;
}


const tnbLib::labelListList& tnbLib::primitiveMesh::faceEdges() const
{
	if (!fePtr_)
	{
		// 1.6.x merge: reverting to correct code
		// HJ, 17/Aug/2010
		calcEdges();
	}

	return *fePtr_;
}


void tnbLib::primitiveMesh::clearOutEdges()
{
	deleteDemandDrivenData(edgesPtr_);
	deleteDemandDrivenData(fePtr_);
	labels_.clear();
	labelSet_.clear();
}


const tnbLib::labelList& tnbLib::primitiveMesh::faceEdges
(
	const label faceI,
	dynamicLabelList& storage
) const
{
	if (hasFaceEdges())
	{
		return faceEdges()[faceI];
	}
	else
	{
		const labelListList& pointEs = pointEdges();
		const face& f = faces()[faceI];

		storage.clear();
		if (f.size() > storage.capacity())
		{
			storage.setCapacity(f.size());
		}

		forAll(f, fp)
		{
			storage.append
			(
				findFirstCommonElementFromSortedLists
				(
					pointEs[f[fp]],
					pointEs[f.nextLabel(fp)]
				)
			);
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::faceEdges(const label faceI) const
{
	return faceEdges(faceI, labels_);
}


const tnbLib::labelList& tnbLib::primitiveMesh::cellEdges
(
	const label cellI,
	dynamicLabelList& storage
) const
{
	if (hasCellEdges())
	{
		return cellEdges()[cellI];
	}
	else
	{
		const labelList& cFaces = cells()[cellI];

		labelSet_.clear();

		forAll(cFaces, i)
		{
			const labelList& fe = faceEdges(cFaces[i]);

			forAll(fe, feI)
			{
				labelSet_.insert(fe[feI]);
			}
		}

		storage.clear();

		if (labelSet_.size() > storage.capacity())
		{
			storage.setCapacity(labelSet_.size());
		}

		forAllConstIter(labelHashSet, labelSet_, iter)
		{
			storage.append(iter.key());
		}

		return storage;
	}
}


const tnbLib::labelList& tnbLib::primitiveMesh::cellEdges(const label cellI) const
{
	return cellEdges(cellI, labels_);
}


// ************************************************************************* //