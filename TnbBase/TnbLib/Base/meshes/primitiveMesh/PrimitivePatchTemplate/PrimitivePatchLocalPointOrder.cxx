#include <PrimitivePatchTemplate.hxx>

#include <SLList.hxx>
#include <boolList.hxx>

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
calcLocalPointOrder() const
{
	// Note: Cannot use bandCompressing as point-point addressing does
	// not exist and is not considered generally useful.
	//

	if (debug)
	{
		Pout << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcLocalPointOrder() : "
			<< "calculating local point order"
			<< endl;
	}

	if (localPointOrderPtr_)
	{
		// it is considered an error to attempt to recalculate
		// if already allocated
		FatalErrorIn
		(
			"PrimitivePatch<Face, FaceList, PointField, PointType>::"
			"calcLocalPointOrder()"
		) << "local point order already calculated"
			<< abort(FatalError);
	}

	const List<Face>& lf = localFaces();

	const labelListList& ff = faceFaces();

	boolList visitedFace(lf.size(), false);

	localPointOrderPtr_ = new labelList(meshPoints().size(), -1);

	labelList& pointOrder = *localPointOrderPtr_;

	boolList visitedPoint(pointOrder.size(), false);

	label nPoints = 0;

	forAll(lf, faceI)
	{
		if (!visitedFace[faceI])
		{
			SLList<label> faceOrder(faceI);

			do
			{
				const label curFace = faceOrder.first();

				faceOrder.removeHead();

				if (!visitedFace[curFace])
				{
					visitedFace[curFace] = true;

					const labelList& curPoints = lf[curFace];

					// mark points
					forAll(curPoints, pointI)
					{
						if (!visitedPoint[curPoints[pointI]])
						{
							visitedPoint[curPoints[pointI]] = true;

							pointOrder[nPoints] = curPoints[pointI];

							nPoints++;
						}
					}

					// add face neighbours to the list
					const labelList& nbrs = ff[curFace];

					forAll(nbrs, nbrI)
					{
						if (!visitedFace[nbrs[nbrI]])
						{
							faceOrder.append(nbrs[nbrI]);
						}
					}
				}
			} while (faceOrder.size());
		}
	}

	if (debug)
	{
		Pout << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcLocalPointOrder() "
			<< "finished calculating local point order"
			<< endl;
	}
}


// ************************************************************************* //