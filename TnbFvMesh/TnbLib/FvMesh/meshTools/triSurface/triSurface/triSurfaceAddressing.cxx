#include <triSurface.hxx>

#include <HashTable.hxx>
#include <SortableList.hxx>
#include <transform.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void triSurface::calcSortedEdgeFaces() const
	{
		if (sortedEdgeFacesPtr_)
		{
			FatalErrorIn("triSurface::calcSortedEdgeFaces()")
				<< "sortedEdgeFacesPtr_ already set"
				<< abort(FatalError);
		}

		const labelListList& eFaces = edgeFaces();

		// create the lists for the various results. (resized on completion)
		sortedEdgeFacesPtr_ = new labelListList(eFaces.size());
		labelListList& sortedEdgeFaces = *sortedEdgeFacesPtr_;

		forAll(eFaces, edgeI)
		{
			const labelList& myFaceNbs = eFaces[edgeI];

			if (myFaceNbs.size() > 2)
			{
				// Get point on edge and normalized direction of edge (= e2 base
				// of our coordinate system)
				const edge& e = edges()[edgeI];

				const point& edgePt = localPoints()[e.start()];

				vector e2 = e.vec(localPoints());
				e2 /= mag(e2) + VSMALL;


				// Get opposite vertex for 0th face
				const labelledTri& f = localFaces()[myFaceNbs[0]];
				label fp0 = findIndex(f, e[0]);
				label fp1 = f.fcIndex(fp0);
				label vertI = (f[fp1] != e[1] ? f[fp1] : f.fcIndex(fp1));

				// Get vector normal both to e2 and to edge from opposite vertex
				// to edge (will be x-axis of our coordinate system)
				vector e0 = e2 ^ (localPoints()[vertI] - edgePt);
				e0 /= mag(e0) + VSMALL;

				// Get y-axis of coordinate system
				vector e1 = e2 ^ e0;


				SortableList<scalar> faceAngles(myFaceNbs.size());

				// e0 is reference so angle is 0
				faceAngles[0] = 0;

				for (label nbI = 1; nbI < myFaceNbs.size(); nbI++)
				{
					// Get opposite vertex
					const labelledTri& f = localFaces()[myFaceNbs[nbI]];
					label fp0 = findIndex(f, e[0]);
					label fp1 = f.fcIndex(fp0);
					label vertI = (f[fp1] != e[1] ? f[fp1] : f.fcIndex(fp1));

					vector vec = e2 ^ (localPoints()[vertI] - edgePt);
					vec /= mag(vec) + VSMALL;

					faceAngles[nbI] = pseudoAngle
					(
						e0,
						e1,
						vec
					);
				}

				faceAngles.sort();

				sortedEdgeFaces[edgeI] = UIndirectList<label>
					(
						myFaceNbs,
						faceAngles.indices()
						);
			}
			else
			{
				// No need to sort. Just copy.
				sortedEdgeFaces[edgeI] = myFaceNbs;
			}
		}
	}


	void triSurface::calcEdgeOwner() const
	{
		if (edgeOwnerPtr_)
		{
			FatalErrorIn("triSurface::calcEdgeOwner()")
				<< "edgeOwnerPtr_ already set"
				<< abort(FatalError);
		}

		// create the owner list
		edgeOwnerPtr_ = new labelList(nEdges());
		labelList& edgeOwner = *edgeOwnerPtr_;

		forAll(edges(), edgeI)
		{
			const edge& e = edges()[edgeI];

			const labelList& myFaces = edgeFaces()[edgeI];

			if (myFaces.size() == 1)
			{
				edgeOwner[edgeI] = myFaces[0];
			}
			else
			{
				// Find the first face whose vertices are aligned with the edge.
				// (in case of multiply connected edge the best we can do)
				edgeOwner[edgeI] = -1;

				forAll(myFaces, i)
				{
					const labelledTri& f = localFaces()[myFaces[i]];

					if
						(
						((f[0] == e.start()) && (f[1] == e.end()))
							|| ((f[1] == e.start()) && (f[2] == e.end()))
							|| ((f[2] == e.start()) && (f[0] == e.end()))
							)
					{
						edgeOwner[edgeI] = myFaces[i];

						break;
					}
				}

				if (edgeOwner[edgeI] == -1)
				{
					FatalErrorIn("triSurface::calcEdgeOwner()")
						<< "Edge " << edgeI << " vertices:" << e
						<< " is used by faces " << myFaces
						<< " vertices:"
						<< UIndirectList<labelledTri>(localFaces(), myFaces)()
						<< " none of which use the edge vertices in the same order"
						<< nl << "I give up" << abort(FatalError);
				}
			}
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //