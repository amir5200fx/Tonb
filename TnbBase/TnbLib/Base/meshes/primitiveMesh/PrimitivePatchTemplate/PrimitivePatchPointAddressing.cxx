#include <PrimitivePatchTemplate.hxx>

#include <SLList.hxx>

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
calcPointEdges() const
{
	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcPointEdges() : calculating pointEdges"
			<< endl;
	}

	if (pointEdgesPtr_)
	{
		// it is considered an error to attempt to recalculate
		// if already allocated
		FatalErrorIn
		(
			"PrimitivePatch<Face, FaceList, PointField, PointType>::"
			"calcPointEdges()"
		) << "pointEdges already calculated"
			<< abort(FatalError);
	}

	const edgeList& e = edges();

	// set up storage for pointEdges
	List<SLList<label> > pointEdges(meshPoints().size());

	forAll(e, edgeI)
	{
		pointEdges[e[edgeI].start()].append(edgeI);
		pointEdges[e[edgeI].end()].append(edgeI);
	}

	// sort out the list
	pointEdgesPtr_ = new labelListList(pointEdges.size());

	labelListList& pe = *pointEdgesPtr_;

	forAll(pointEdges, pointI)
	{
		pe[pointI].setSize(pointEdges[pointI].size());

		label i = 0;
		for
			(
				SLList<label>::iterator curEdgesIter = pointEdges[pointI].begin();
				curEdgesIter != pointEdges[pointI].end();
				++curEdgesIter, ++i
				)
		{
			pe[pointI][i] = curEdgesIter();
		}
	}

	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcPointEdges() finished calculating pointEdges"
			<< endl;
	}
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
void
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
calcPointFaces() const
{
	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcPointFaces() : calculating pointFaces"
			<< endl;
	}

	if (pointFacesPtr_)
	{
		// it is considered an error to attempt to recalculate
		// if already allocated
		FatalErrorIn
		(
			"PrimitivePatch<Face, FaceList, PointField, PointType>::"
			"calcPointFaces()"
		) << "pointFaces already calculated"
			<< abort(FatalError);
	}

	const List<Face>& f = localFaces();

	// set up storage for pointFaces
	List<SLList<label> > pointFcs(meshPoints().size());

	forAll(f, faceI)
	{
		const Face& curPoints = f[faceI];

		forAll(curPoints, pointI)
		{
			pointFcs[curPoints[pointI]].append(faceI);
		}
	}

	// sort out the list
	pointFacesPtr_ = new labelListList(pointFcs.size());

	labelListList& pf = *pointFacesPtr_;

	forAll(pointFcs, pointI)
	{
		pf[pointI].setSize(pointFcs[pointI].size());

		label i = 0;
		for
			(
				SLList<label>::iterator curFacesIter = pointFcs[pointI].begin();
				curFacesIter != pointFcs[pointI].end();
				++curFacesIter, ++i
				)
		{
			pf[pointI][i] = curFacesIter();
		}
	}

	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "calcPointFaces() finished calculating pointFaces"
			<< endl;
	}
}


// ************************************************************************* //