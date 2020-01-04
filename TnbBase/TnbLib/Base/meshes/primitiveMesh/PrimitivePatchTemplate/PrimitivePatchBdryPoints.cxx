#include <PrimitivePatchTemplate.hxx>

#include <HashSet.hxx>

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
calcBdryPoints() const
{
	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcBdryPoints() : "
			<< "calculating boundary points"
			<< endl;
	}

	if (boundaryPointsPtr_)
	{
		// it is considered an error to attempt to recalculate
		// if already allocated
		FatalErrorIn
		(
			"PrimitivePatch<Face, FaceList, PointField, PointType>::"
			"calcBdryPoints()"
		) << "edge types already calculated"
			<< abort(FatalError);
	}

	const edgeList& e = edges();

	labelHashSet bp(2 * e.size());

	for (label edgeI = nInternalEdges_; edgeI < e.size(); edgeI++)
	{
		const edge& curEdge = e[edgeI];

		bp.insert(curEdge.start());
		bp.insert(curEdge.end());
	}

	boundaryPointsPtr_ = new labelList(bp.toc());
	sort(*boundaryPointsPtr_);

	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcBdryPoints() : "
			<< "finished calculating boundary points"
			<< endl;
	}
}


// ************************************************************************* //