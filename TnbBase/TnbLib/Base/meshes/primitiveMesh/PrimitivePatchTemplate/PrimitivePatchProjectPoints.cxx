#include <PrimitivePatchTemplate.hxx>

#include <PointHitTemplate.hxx>
#include <objectHit.hxx>
#include <bandCompression.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
template <class ToPatch>
tnbLib::List<tnbLib::objectHit>
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
projectPoints
(
	const ToPatch& targetPatch,
	const Field<PointType>& projectionDirection,
	const intersection::algorithm alg,
	const intersection::direction dir
) const
{
	// The current patch is slave, i.e. it is being projected onto the target

	if (projectionDirection.size() != nPoints())
	{
		FatalErrorIn
		(
			"PrimitivePatch<Face, FaceList, PointField, PointType>::"
			"projectPoints(const PrimitivePatch& "
			", const Field<PointType>&) const"
		) << "Projection direction field does not correspond to "
			<< "patch points." << endl
			<< "Size: " << projectionDirection.size()
			<< " Number of points: " << nPoints()
			<< abort(FatalError);
	}

	const labelList& slavePointOrder = localPointOrder();

	const labelList& slaveMeshPoints = meshPoints();

	// Result
	List<objectHit> result(nPoints());

	// If there are no faces in the master patch, return: all misses
	if (targetPatch.size() == 0)
	{
		// Null-constructed object hit is a miss
		return result;
	}

	const labelListList& masterFaceFaces = targetPatch.faceFaces();

	const ToPatch& masterFaces = targetPatch;

	const Field<PointType>& masterPoints = targetPatch.points();

	// Estimate face centre of target side
	Field<PointType> masterFaceCentres(targetPatch.size());

	forAll(masterFaceCentres, faceI)
	{
		masterFaceCentres[faceI] =
			average(masterFaces[faceI].points(masterPoints));
	}

	// Algorithm:
	// Loop through all points of the slave side. For every point find the
	// radius for the current contact face. If the contact point falls inside
	// the face and the radius is smaller than for all neighbouring faces,
	// the contact is found. If not, visit the neighbour closest to the
	// calculated contact point. If a single master face is visited more than
	// twice, initiate n-squared search.

	if (debug)
	{
		Info << "N-squared projection set for all points" << endl;
	}

	label curFace = 0;
	label nNSquaredSearches = 0;

	forAll(slavePointOrder, pointI)
	{
		// Pick up slave point and direction
		const label curLocalPointLabel = slavePointOrder[pointI];

		const PointType& curPoint =
			points_[slaveMeshPoints[curLocalPointLabel]];

		const PointType& curProjectionDir =
			projectionDirection[curLocalPointLabel];

		bool closer;

		boolList visitedTargetFace(targetPatch.size(), false);
		bool doNSquaredSearch = false;

		bool foundEligible = false;

		scalar sqrDistance = GREAT;

		// Force the full search for the first point to ensure good
		// starting face
		if (pointI == 0)
		{
			doNSquaredSearch = true;
		}
		else
		{
			do
			{
				closer = false;
				doNSquaredSearch = false;

				// Calculate intersection with curFace
				PointHit<PointType> curHit =
					masterFaces[curFace].ray
					(
						curPoint,
						curProjectionDir,
						masterPoints,
						alg,
						dir
					);

				visitedTargetFace[curFace] = true;

				if (curHit.hit())
				{
					result[curLocalPointLabel] = objectHit(true, curFace);

					break;
				}
				else
				{
					// If a new miss is eligible, it is closer than
					// any previous eligible miss (due to surface walk)

					// Only grab the miss if it is eligible
					if (curHit.eligibleMiss())
					{
						foundEligible = true;
						result[curLocalPointLabel] = objectHit(false, curFace);
					}

					// Find the next likely face for intersection

					// Calculate the miss point on the plane of the
					// face.  This is cooked (illogical!) for fastest
					// surface walk.
					//
					PointType missPlanePoint =
						curPoint + curProjectionDir * curHit.distance();

					const labelList& masterNbrs = masterFaceFaces[curFace];

					sqrDistance =
						magSqr(missPlanePoint - masterFaceCentres[curFace]);

					forAll(masterNbrs, nbrI)
					{
						if
							(
								magSqr
								(
									missPlanePoint
									- masterFaceCentres[masterNbrs[nbrI]]
								)
								<= sqrDistance
								)
						{
							closer = true;
							curFace = masterNbrs[nbrI];
						}
					}

					if (visitedTargetFace[curFace])
					{
						// This face has already been visited.
						// Execute n-squared search
						doNSquaredSearch = true;
						break;
					}
				}

				if (debug) Info << ".";
			} while (closer);
		}

		if (doNSquaredSearch || !foundEligible)
		{
			nNSquaredSearches++;

			if (debug)
			{
				Info << "p " << curLocalPointLabel << ": ";
			}

			// Improved n-sqared search algorithm.  HJ, 25/Nov/2006
			result[curLocalPointLabel] = objectHit(false, -1);
			scalar minMissDistance = GREAT;
			scalar minHitDistance = GREAT;
			bool hitFound = false;

			forAll(masterFaces, faceI)
			{
				PointHit<PointType> curHit =
					masterFaces[faceI].ray
					(
						curPoint,
						curProjectionDir,
						masterPoints,
						alg,
						dir
					);

				if (curHit.hit())
				{
					// Calculate min distance
					scalar hitDist =
						tnbLib::mag(curHit.hitPoint() - curPoint);

					if (hitDist < minHitDistance)
					{
						result[curLocalPointLabel] = objectHit(true, faceI);

						hitFound = true;
						curFace = faceI;
						minHitDistance = hitDist;
					}
				}
				else if (curHit.eligibleMiss() && !hitFound)
				{
					// Calculate min distance
					scalar missDist =
						tnbLib::mag(curHit.missPoint() - curPoint);

					if (missDist < minMissDistance)
					{
						minMissDistance = missDist;

						result[curLocalPointLabel] = objectHit(false, faceI);
						curFace = faceI;
					}
				}
			}

			if (debug)
			{
				Info << result[curLocalPointLabel]
					<< " hit = " << minHitDistance
					<< " miss = " << minMissDistance << nl;
			}
		}
		else
		{
			if (debug) Info << "x";
		}
	}

	if (debug)
	{
		Info << nl << "Executed " << nNSquaredSearches
			<< " n-squared searches out of total of "
			<< nPoints() << endl;
	}

	return result;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
template <class ToPatch>
tnbLib::List<tnbLib::objectHit>
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
projectFaceCentres
(
	const ToPatch& targetPatch,
	const Field<PointType>& projectionDirection,
	const intersection::algorithm alg,
	const intersection::direction dir
) const
{
	// The current patch is slave, i.e. it is being projected onto the target

	if (projectionDirection.size() != this->size())
	{
		FatalErrorIn
		(
			"labelList PrimitivePatch<Face, FaceList, PointField, PointType>::"
			"projectFaceCentres(const PrimitivePatch& "
			", const Field<PointType>&) const"
		) << "Projection direction field does not correspond to patch faces."
			<< endl << "Size: " << projectionDirection.size()
			<< " Number of points: " << this->size()
			<< abort(FatalError);
	}

	labelList slaveFaceOrder = bandCompression(faceFaces());

	// calculate master face centres
	Field<PointType> masterFaceCentres(targetPatch.size());

	const labelListList& masterFaceFaces = targetPatch.faceFaces();

	const ToPatch& masterFaces = targetPatch;

	const Field<PointType>& masterPoints = targetPatch.points();

	forAll(masterFaceCentres, faceI)
	{
		masterFaceCentres[faceI] =
			masterFaces[faceI].centre(masterPoints);
	}

	// Result
	List<objectHit> result(this->size());

	// If there are no faces in the master patch, return: all misses
	if (targetPatch.size() == 0)
	{
		// Null-constructed object hit is a miss
		return result;
	}

	const PrimitivePatch<Face, FaceList, PointField>& slaveFaces = *this;
	const vectorField& slaveGlobalPoints = points();

	// Algorithm:
	// Loop through all points of the slave side. For every point find the
	// radius for the current contact face. If the contact point falls inside
	// the face and the radius is smaller than for all neighbouring faces,
	// the contact is found. If not, visit the neighbour closest to the
	// calculated contact point. If a single master face is visited more than
	// twice, initiate n-squared search.

	label curFace = 0;
	label nNSquaredSearches = 0;

	forAll(slaveFaceOrder, faceI)
	{
		// pick up slave point and direction
		const label curLocalFaceLabel = slaveFaceOrder[faceI];

		const point& curFaceCentre =
			slaveFaces[curLocalFaceLabel].centre(slaveGlobalPoints);

		const vector& curProjectionDir =
			projectionDirection[curLocalFaceLabel];

		bool closer;

		boolList visitedTargetFace(targetPatch.size(), false);
		bool doNSquaredSearch = false;

		bool foundEligible = false;

		scalar sqrDistance = GREAT;

		// Force the full search for the first point to ensure good
		// starting face
		if (faceI == 0 || nSquaredProjection_() > 0)
		{
			doNSquaredSearch = true;
		}
		else
		{
			do
			{
				closer = false;
				doNSquaredSearch = false;

				// Calculate intersection with curFace
				PointHit<PointType> curHit =
					masterFaces[curFace].ray
					(
						curFaceCentre,
						curProjectionDir,
						masterPoints,
						alg,
						dir
					);

				visitedTargetFace[curFace] = true;

				if (curHit.hit())
				{
					result[curLocalFaceLabel] = objectHit(true, curFace);

					break;
				}
				else
				{
					// If a new miss is eligible, it is closer than
					// any previous eligible miss (due to surface walk)

					// Only grab the miss if it is eligible
					if (curHit.eligibleMiss())
					{
						foundEligible = true;
						result[curLocalFaceLabel] = objectHit(false, curFace);
					}

					// Find the next likely face for intersection

					// Calculate the miss point.  This is
					// cooked (illogical!) for fastest surface walk.
					//
					PointType missPlanePoint =
						curFaceCentre + curProjectionDir * curHit.distance();

					sqrDistance =
						magSqr(missPlanePoint - masterFaceCentres[curFace]);

					const labelList& masterNbrs = masterFaceFaces[curFace];

					forAll(masterNbrs, nbrI)
					{
						if
							(
								magSqr
								(
									missPlanePoint
									- masterFaceCentres[masterNbrs[nbrI]]
								)
								<= sqrDistance
								)
						{
							closer = true;
							curFace = masterNbrs[nbrI];
						}
					}

					if (visitedTargetFace[curFace])
					{
						// This face has already been visited.
						// Execute n-squared search
						doNSquaredSearch = true;
						break;
					}
				}

				if (debug) Info << ".";
			} while (closer);
		}

		if (doNSquaredSearch || !foundEligible)
		{
			nNSquaredSearches++;

			if (debug)
			{
				Info << "p " << curLocalFaceLabel << ": ";
			}

			// Improved n-sqared search algorithm.  HJ, 25/Nov/2006
			result[curLocalFaceLabel] = objectHit(false, -1);
			scalar minMissDistance = GREAT;
			scalar minHitDistance = GREAT;
			bool hitFound = false;

			forAll(masterFaces, faceI)
			{
				PointHit<PointType> curHit =
					masterFaces[faceI].ray
					(
						curFaceCentre,
						curProjectionDir,
						masterPoints,
						alg,
						dir
					);

				if (curHit.hit())
				{
					// Calculate min distance
					scalar hitDist =
						tnbLib::mag(curHit.hitPoint() - curFaceCentre);

					if (hitDist < minHitDistance)
					{
						result[curLocalFaceLabel] = objectHit(true, faceI);

						hitFound = true;
						curFace = faceI;
						minHitDistance = hitDist;
					}
				}
				else if (curHit.eligibleMiss() && !hitFound)
				{
					// Calculate min distance
					scalar missDist =
						tnbLib::mag(curHit.missPoint() - curFaceCentre);

					if (missDist < minMissDistance)
					{
						minMissDistance = missDist;

						result[curLocalFaceLabel] = objectHit(false, faceI);
						curFace = faceI;
					}
				}
			}

			if (debug)
			{
				Info << "r = " << result[curLocalFaceLabel] << nl;
			}
		}
		else
		{
			if (debug) Info << "x";
		}
	}

	if (debug)
	{
		Info << nl << "Executed " << nNSquaredSearches
			<< " n-squared searches out of total of "
			<< this->size() << endl;
	}

	return result;
}


// ************************************************************************* //