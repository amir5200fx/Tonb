#include <PrimitivePatchTemplate.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
void
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
clearGeom()
{
	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "clearGeom() : clearing geometric data"
			<< endl;
	}

	deleteDemandDrivenData(localPointsPtr_);
	deleteDemandDrivenData(faceCentresPtr_);
	deleteDemandDrivenData(faceNormalsPtr_);
	deleteDemandDrivenData(pointNormalsPtr_);
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
clearTopology()
{
	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "clearTopology() : clearing patch addressing"
			<< endl;
	}

	// group created and destroyed together
	if (edgesPtr_ && faceFacesPtr_ && edgeFacesPtr_ && faceEdgesPtr_)
	{
		delete edgesPtr_;
		edgesPtr_ = NULL;

		delete faceFacesPtr_;
		faceFacesPtr_ = NULL;

		delete edgeFacesPtr_;
		edgeFacesPtr_ = NULL;

		delete faceEdgesPtr_;
		faceEdgesPtr_ = NULL;
	}

	deleteDemandDrivenData(boundaryPointsPtr_);
	deleteDemandDrivenData(pointEdgesPtr_);
	deleteDemandDrivenData(pointFacesPtr_);
	deleteDemandDrivenData(edgeLoopsPtr_);
	deleteDemandDrivenData(localPointOrderPtr_);
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
clearPatchMeshAddr()
{
	if (debug)
	{
		Info << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "clearPatchMeshAddr() : "
			<< "clearing patch-mesh addressing"
			<< endl;
	}

	deleteDemandDrivenData(meshPointsPtr_);
	deleteDemandDrivenData(meshPointMapPtr_);
	deleteDemandDrivenData(localFacesPtr_);
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
clearOut()
{
	clearGeom();
	clearTopology();
	clearPatchMeshAddr();
}


// ************************************************************************* //