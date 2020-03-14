#include <triSurface.hxx>

#include <mergePoints.hxx>
#include <PackedBoolList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	bool triSurface::stitchTriangles
	(
		const pointField& rawPoints,
		const scalar tol,
		bool verbose
	)
	{
		// Merge points
		labelList pointMap;
		pointField newPoints;
		bool hasMerged = mergePoints(rawPoints, tol, verbose, pointMap, newPoints);

		if (hasMerged)
		{
			if (verbose)
			{
				Pout << "stitchTriangles : Merged from " << rawPoints.size()
					<< " points down to " << newPoints.size() << endl;
			}

			// Reset the triangle point labels to the unique points array
			label newTriangleI = 0;
			forAll(*this, i)
			{
				const labelledTri& tri = operator[](i);
				labelledTri newTri
				(
					pointMap[tri[0]],
					pointMap[tri[1]],
					pointMap[tri[2]],
					tri.region()
				);

				if
					(
					(newTri[0] != newTri[1])
						&& (newTri[0] != newTri[2])
						&& (newTri[1] != newTri[2])
						)
				{
					operator[](newTriangleI++) = newTri;
				}
				else if (verbose)
				{
					Pout << "stitchTriangles : "
						<< "Removing triangle " << i
						<< " with non-unique vertices." << endl
						<< "    vertices   :" << newTri << endl
						<< "    coordinates:" << newTri.points(newPoints)
						<< endl;
				}
			}

			// If empty triangles are detected, remove them from the list
			if (newTriangleI != size())
			{
				if (verbose)
				{
					Pout << "stitchTriangles : "
						<< "Removed " << size() - newTriangleI
						<< " triangles" << endl;
				}
				setSize(newTriangleI);

				// Possibly compact out any unused points (since used only
				// by triangles that have just been deleted)
				// Done in two passes to save memory (pointField)

				// 1. Detect only
				PackedBoolList pointIsUsed(newPoints.size());

				label nPoints = 0;

				forAll(*this, i)
				{
					const labelledTri& tri = operator[](i);

					forAll(tri, fp)
					{
						label pointI = tri[fp];
						if (pointIsUsed.set(pointI, 1))
						{
							nPoints++;
						}
					}
				}

				if (nPoints != newPoints.size())
				{
					// 2. Compact.
					pointMap.setSize(newPoints.size());
					label newPointI = 0;
					forAll(pointIsUsed, pointI)
					{
						if (pointIsUsed[pointI])
						{
							newPoints[newPointI] = newPoints[pointI];
							pointMap[pointI] = newPointI++;
						}
					}
					newPoints.setSize(newPointI);

					newTriangleI = 0;
					forAll(*this, i)
					{
						const labelledTri& tri = operator[](i);
						operator[](newTriangleI++) = labelledTri
						(
							pointMap[tri[0]],
							pointMap[tri[1]],
							pointMap[tri[2]],
							tri.region()
						);
					}
				}
			}

			// Set the coordinates to the merged ones
			storedPoints().transfer(newPoints);
		}

		return hasMerged;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //