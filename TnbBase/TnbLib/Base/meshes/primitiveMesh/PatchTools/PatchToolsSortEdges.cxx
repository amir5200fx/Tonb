#include <PatchTools.hxx>

#include <SortableList.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
tnbLib::labelListList
tnbLib::PatchTools::sortedEdgeFaces
(
	const PrimitivePatch<Face, FaceList, PointField, PointType>& p
)
{
	const edgeList& edges = p.edges();
	const labelListList& edgeFaces = p.edgeFaces();
	const List<Face>& localFaces = p.localFaces();
	const Field<PointType>& localPoints = p.localPoints();

	// create the lists for the various results. (resized on completion)
	labelListList sortedEdgeFaces(edgeFaces.size());

	forAll(edgeFaces, edgeI)
	{
		const labelList& faceNbs = edgeFaces[edgeI];

		if (faceNbs.size() > 2)
		{
			// Get point on edge and normalized direction of edge (= e2 base
			// of our coordinate system)
			const edge& e = edges[edgeI];

			const point& edgePt = localPoints[e.start()];

			vector e2 = e.vec(localPoints);
			e2 /= mag(e2) + VSMALL;

			// Get opposite vertex for 0th face
			const Face& f = localFaces[faceNbs[0]];

			label fp0 = findIndex(f, e[0]);
			label fp1 = f.fcIndex(fp0);
			label vertI = (f[fp1] != e[1] ? f[fp1] : f.fcIndex(fp1));

			// Get vector normal both to e2 and to edge from opposite vertex
			// to edge (will be x-axis of our coordinate system)
			vector e0 = e2 ^ (localPoints[vertI] - edgePt);
			e0 /= mag(e0) + VSMALL;

			// Get y-axis of coordinate system
			vector e1 = e2 ^ e0;

			SortableList<scalar> faceAngles(faceNbs.size());

			// e0 is reference so angle is 0
			faceAngles[0] = 0;

			for (label nbI = 1; nbI < faceNbs.size(); nbI++)
			{
				// Get opposite vertex
				const Face& f = localFaces[faceNbs[nbI]];
				label fp0 = findIndex(f, e[0]);
				label fp1 = f.fcIndex(fp0);
				label vertI = (f[fp1] != e[1] ? f[fp1] : f.fcIndex(fp1));

				vector vec = e2 ^ (localPoints[vertI] - edgePt);
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
					faceNbs,
					faceAngles.indices()
					);
		}
		else
		{
			// No need to sort. Just copy.
			sortedEdgeFaces[edgeI] = faceNbs;
		}
	}

	return sortedEdgeFaces;
}


// ************************************************************************* //