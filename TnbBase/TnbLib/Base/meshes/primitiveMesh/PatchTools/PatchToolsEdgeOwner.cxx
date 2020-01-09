#include <PatchTools.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
tnbLib::labelList
tnbLib::PatchTools::edgeOwner
(
	const PrimitivePatch<Face, FaceList, PointField, PointType>& p
)
{
	const edgeList& edges = p.edges();
	const labelListList& edgeFaces = p.edgeFaces();
	const List<Face>& localFaces = p.localFaces();

	// create the owner list
	labelList edgeOwner(edges.size(), -1);

	forAll(edges, edgeI)
	{
		const labelList& nbrFaces = edgeFaces[edgeI];

		if (nbrFaces.size() == 1)
		{
			edgeOwner[edgeI] = nbrFaces[0];
		}
		else
		{
			// Find the first face whose vertices are aligned with the edge.
			// with multiply connected edges, this is the best we can do
			forAll(nbrFaces, i)
			{
				const Face& f = localFaces[nbrFaces[i]];

				if (f.edgeDirection(edges[edgeI]) > 0)
				{
					edgeOwner[edgeI] = nbrFaces[i];
					break;
				}
			}

			if (edgeOwner[edgeI] == -1)
			{
				FatalErrorIn
				(
					"PatchTools::edgeOwner()"
				)
					<< "Edge " << edgeI << " vertices:" << edges[edgeI]
					<< " is used by faces " << nbrFaces
					<< " vertices:"
					<< UIndirectList<Face>(localFaces, nbrFaces)()
					<< " none of which use the edge vertices in the same order"
					<< nl << "I give up" << abort(FatalError);
			}
		}
	}

	return edgeOwner;
}


// ************************************************************************* //