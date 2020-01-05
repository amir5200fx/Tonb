#include <mergePoints.hxx>

#include <SortableList.hxx>
#include <ListOps.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::mergePoints
(
	const UList<point>& points,
	const scalar mergeTol,
	const bool verbose,
	labelList& pointMap,
	List<point>& newPoints,
	const point& origin
)
{
	point compareOrigin = origin;

	if (origin == point(VGREAT, VGREAT, VGREAT))
	{
		if (points.size())
		{
			compareOrigin = sum(points) / points.size();
		}
	}

	// Create a old to new point mapping array
	pointMap.setSize(points.size());
	pointMap = -1;

	// Storage for merged points
	newPoints.setSize(points.size());

	if (points.empty())
	{
		return false;
	}


	const scalar mergeTolSqr = sqr(mergeTol);

	// Sort points by magSqr
	SortableList<scalar> sortedMagSqr(magSqr(points - compareOrigin));

	bool hasMerged = false;

	label newPointI = 0;


	// Handle 0th point separately (is always unique)
	label pointI = sortedMagSqr.indices()[0];
	pointMap[pointI] = newPointI;
	newPoints[newPointI++] = points[pointI];


	for (label sortI = 1; sortI < sortedMagSqr.size(); sortI++)
	{
		// Get original point index
		label pointI = sortedMagSqr.indices()[sortI];

		// Compare to previous points to find equal one.
		label equalPointI = -1;

		for
			(
				label prevSortI = sortI - 1;
				prevSortI >= 0
				&& mag
				(
					sortedMagSqr[prevSortI]
					- sortedMagSqr[sortI]
				) <= mergeTolSqr;
				prevSortI--
				)
		{
			label prevPointI = sortedMagSqr.indices()[prevSortI];

			if (magSqr(points[pointI] - points[prevPointI]) <= mergeTolSqr)
			{
				// Found match.
				equalPointI = prevPointI;

				break;
			}
		}


		if (equalPointI != -1)
		{
			// Same coordinate as equalPointI. Map to same new point.
			pointMap[pointI] = pointMap[equalPointI];

			hasMerged = true;

			if (verbose)
			{
				Pout << "tnbLib::mergePoints : Merging points "
					<< pointI << " and " << equalPointI
					<< " with coordinates:" << points[pointI]
					<< " and " << points[equalPointI]
					<< endl;
			}
		}
		else
		{
			// Differs. Store new point.
			pointMap[pointI] = newPointI;
			newPoints[newPointI++] = points[pointI];
		}
	}

	newPoints.setSize(newPointI);

	return hasMerged;
}


// ************************************************************************* //
