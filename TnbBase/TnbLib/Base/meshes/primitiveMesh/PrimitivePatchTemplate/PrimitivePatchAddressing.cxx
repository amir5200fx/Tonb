#include <PrimitivePatchTemplate.hxx>

#include <dynamicLabelList.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
void
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
calcAddressing() const
{
	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcAddressing() : calculating patch addressing"
			<< endl;
	}

	if (edgesPtr_ || faceFacesPtr_ || edgeFacesPtr_ || faceEdgesPtr_)
	{
		// it is considered an error to attempt to recalculate
		// if already allocated
		FatalErrorIn
		(
			"PrimitivePatch<Face, FaceList, PointField, PointType>::"
			"calcAddressing()"
		) << "addressing already calculated"
			<< abort(FatalError);
	}

	if (this->size() == 0)
	{
		// No faces in patch.  All lists are empty

		edgesPtr_ = new edgeList(0);
		faceFacesPtr_ = new labelListList(0);
		edgeFacesPtr_ = new labelListList(0);
		faceEdgesPtr_ = new labelListList(0);
		nInternalEdges_ = 0;

		return;
	}

	// Get reference to localFaces
	const List<Face>& locFcs = localFaces();

	// Get reference to pointFaces
	const labelListList& pf = pointFaces();

	// Guess the max number of edges and neighbours for a face
	label maxEdges = 0;
	forAll(locFcs, faceI)
	{
		maxEdges += locFcs[faceI].size();
	}

	// Create the lists for the various results. (resized on completion)
	edgesPtr_ = new edgeList(maxEdges);
	edgeList& edges = *edgesPtr_;

	edgeFacesPtr_ = new labelListList(maxEdges);
	labelListList& edgeFaces = *edgeFacesPtr_;

	// faceFaces created using a dynamic list.  Cannot guess size because
	// of multiple connections
	List<dynamicLabelList > ff(locFcs.size());

	faceEdgesPtr_ = new labelListList(locFcs.size());
	labelListList& faceEdges = *faceEdgesPtr_;

	// Count the number of face neighbours
	labelList noFaceFaces(locFcs.size());

	// initialise the lists of subshapes for each face to avoid duplication
	edgeListList faceIntoEdges(locFcs.size());

	forAll(locFcs, faceI)
	{
		faceIntoEdges[faceI] = locFcs[faceI].edges();

		labelList& curFaceEdges = faceEdges[faceI];
		curFaceEdges.setSize(faceIntoEdges[faceI].size());

		forAll(curFaceEdges, faceEdgeI)
		{
			curFaceEdges[faceEdgeI] = -1;
		}
	}

	// This algorithm will produce a separated list of edges, internal edges
	// starting from 0 and boundary edges starting from the top and
	// growing down.

	label nEdges = 0;

	bool found = false;

	// Note that faceIntoEdges is sorted acc. to local vertex numbering
	// in face (i.e. curEdges[0] is edge between f[0] and f[1])

	// For all local faces ...
	forAll(locFcs, faceI)
	{
		// Get reference to vertices of current face and corresponding edges.
		const Face& curF = locFcs[faceI];
		const edgeList& curEdges = faceIntoEdges[faceI];

		// Record the neighbour face.  Multiple connectivity allowed
		List<dynamicLabelList > neiFaces(curF.size());
		List<dynamicLabelList > edgeOfNeiFace(curF.size());

		label nNeighbours = 0;

		// For all edges ...
		forAll(curEdges, edgeI)
		{
			// If the edge is already detected, skip
			if (faceEdges[faceI][edgeI] >= 0) continue;

			found = false;

			// Set reference to the current edge
			const edge& e = curEdges[edgeI];

			// Collect neighbours for the current face vertex.

			const labelList& nbrFaces = pf[e.start()];

			forAll(nbrFaces, nbrFaceI)
			{
				// set reference to the current neighbour
				label curNei = nbrFaces[nbrFaceI];

				// Reject neighbours with the lower label
				if (curNei > faceI)
				{
					// get the reference to subshapes of the neighbour
					const edgeList& searchEdges = faceIntoEdges[curNei];

					forAll(searchEdges, neiEdgeI)
					{
						if (searchEdges[neiEdgeI] == e)
						{
							// Match
							found = true;

							neiFaces[edgeI].append(curNei);
							edgeOfNeiFace[edgeI].append(neiEdgeI);

							// Record faceFaces both ways
							ff[faceI].append(curNei);
							ff[curNei].append(faceI);

							// Keep searching due to multiple connectivity
						}
					}
				}
			} // End of neighbouring faces

			if (found)
			{
				// Register another detected internal edge
				nNeighbours++;
			}
		} // End of current edges

		// Add the edges in increasing number of neighbours.
		// Note: for multiply connected surfaces, the lower index neighbour for
		// an edge will come first.

		// Add the faces in the increasing order of neighbours
		for (label neiSearch = 0; neiSearch < nNeighbours; neiSearch++)
		{
			// Find the lowest neighbour which is still valid
			label nextNei = -1;
			label minNei = locFcs.size();

			forAll(neiFaces, nfI)
			{
				if (neiFaces[nfI].size() && neiFaces[nfI][0] < minNei)
				{
					nextNei = nfI;
					minNei = neiFaces[nfI][0];
				}
			}

			if (nextNei > -1)
			{
				// Add the face to the list of faces
				edges[nEdges] = curEdges[nextNei];

				// Set face-edge and face-neighbour-edge to current face label
				faceEdges[faceI][nextNei] = nEdges;

				dynamicLabelList& cnf = neiFaces[nextNei];
				dynamicLabelList& eonf = edgeOfNeiFace[nextNei];

				// Set edge-face addressing
				labelList& curEf = edgeFaces[nEdges];
				curEf.setSize(cnf.size() + 1);
				curEf[0] = faceI;

				forAll(cnf, cnfI)
				{
					faceEdges[cnf[cnfI]][eonf[cnfI]] = nEdges;

					curEf[cnfI + 1] = cnf[cnfI];
				}

				// Stop the neighbour from being used again
				cnf.clear();
				eonf.clear();

				// Increment number of faces counter
				nEdges++;
			}
			else
			{
				FatalErrorIn
				(
					"PrimitivePatch<Face, FaceList, PointField, PointType>::"
					"calcAddressing()"
				) << "Error in internal edge insertion"
					<< abort(FatalError);
			}
		}
	}

	nInternalEdges_ = nEdges;

	// Do boundary faces

	forAll(faceEdges, faceI)
	{
		labelList& curEdges = faceEdges[faceI];

		forAll(curEdges, edgeI)
		{
			if (curEdges[edgeI] < 0)
			{
				// Grab edge and faceEdge
				edges[nEdges] = faceIntoEdges[faceI][edgeI];
				curEdges[edgeI] = nEdges;

				// Add edgeFace
				labelList& curEf = edgeFaces[nEdges];
				curEf.setSize(1);
				curEf[0] = faceI;

				nEdges++;
			}
		}
	}

	// edges
	edges.setSize(nEdges);

	// edgeFaces list
	edgeFaces.setSize(nEdges);

	// faceFaces list
	faceFacesPtr_ = new labelListList(locFcs.size());
	labelListList& faceFaces = *faceFacesPtr_;

	forAll(faceFaces, faceI)
	{
		faceFaces[faceI].transfer(ff[faceI]);
	}


	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcAddressing() : finished calculating patch addressing"
			<< endl;
	}
}


// ************************************************************************* //