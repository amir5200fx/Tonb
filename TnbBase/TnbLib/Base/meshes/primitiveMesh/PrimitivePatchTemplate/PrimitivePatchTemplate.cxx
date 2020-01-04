#include <PrimitivePatchTemplate.hxx>

#include <Map.hxx>
#include <tnbDebug.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::debug::optimisationSwitch
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
nSquaredProjection_
(
	"nSquaredProjection",
	0
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
PrimitivePatch
(
	const FaceList<Face>& faces,
	const Field<PointType>& points
)
	:
	FaceList<Face>(faces),
	points_(points),
	edgesPtr_(NULL),
	nInternalEdges_(-1),
	boundaryPointsPtr_(NULL),
	faceFacesPtr_(NULL),
	edgeFacesPtr_(NULL),
	faceEdgesPtr_(NULL),
	pointEdgesPtr_(NULL),
	pointFacesPtr_(NULL),
	localFacesPtr_(NULL),
	meshPointsPtr_(NULL),
	meshPointMapPtr_(NULL),
	edgeLoopsPtr_(NULL),
	localPointsPtr_(NULL),
	localPointOrderPtr_(NULL),
	faceCentresPtr_(NULL),
	faceNormalsPtr_(NULL),
	pointNormalsPtr_(NULL)
{
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
PrimitivePatch
(
	FaceList<Face>& faces,
	Field<PointType>& points,
	const bool reUse
)
	:
	FaceList<Face>(faces, reUse),
	points_(points, reUse),
	edgesPtr_(NULL),
	nInternalEdges_(-1),
	boundaryPointsPtr_(NULL),
	faceFacesPtr_(NULL),
	edgeFacesPtr_(NULL),
	faceEdgesPtr_(NULL),
	pointEdgesPtr_(NULL),
	pointFacesPtr_(NULL),
	localFacesPtr_(NULL),
	meshPointsPtr_(NULL),
	meshPointMapPtr_(NULL),
	edgeLoopsPtr_(NULL),
	localPointsPtr_(NULL),
	localPointOrderPtr_(NULL),
	faceCentresPtr_(NULL),
	faceNormalsPtr_(NULL),
	pointNormalsPtr_(NULL)
{}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
PrimitivePatch
(
	const PrimitivePatch<Face, FaceList, PointField, PointType>& pp
)
	:
	PrimitivePatchName(),
	FaceList<Face>(pp),
	points_(pp.points_),
	edgesPtr_(NULL),
	nInternalEdges_(-1),
	boundaryPointsPtr_(NULL),
	faceFacesPtr_(NULL),
	edgeFacesPtr_(NULL),
	faceEdgesPtr_(NULL),
	pointEdgesPtr_(NULL),
	pointFacesPtr_(NULL),
	localFacesPtr_(NULL),
	meshPointsPtr_(NULL),
	meshPointMapPtr_(NULL),
	edgeLoopsPtr_(NULL),
	localPointsPtr_(NULL),
	localPointOrderPtr_(NULL),
	faceCentresPtr_(NULL),
	faceNormalsPtr_(NULL),
	pointNormalsPtr_(NULL)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
~PrimitivePatch()
{
	clearOut();
}


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
movePoints
(
	const Field<PointType>&
)
{
	if (debug)
	{
		Pout << "PrimitivePatch<Face, FaceList, PointField, PointType>::"
			<< "movePoints() : "
			<< "recalculating PrimitivePatch geometry following mesh motion"
			<< endl;
	}

	clearGeom();
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::edgeList&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
edges() const
{
	if (!edgesPtr_)
	{
		calcAddressing();
	}

	return *edgesPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
tnbLib::label
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
nInternalEdges() const
{
	if (!edgesPtr_)
	{
		calcAddressing();
	}

	return nInternalEdges_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::labelList&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
boundaryPoints() const
{
	if (!boundaryPointsPtr_)
	{
		calcBdryPoints();
	}

	return *boundaryPointsPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
faceFaces() const
{
	if (!faceFacesPtr_)
	{
		calcAddressing();
	}

	return *faceFacesPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
edgeFaces() const
{
	if (!edgeFacesPtr_)
	{
		calcAddressing();
	}

	return *edgeFacesPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
faceEdges() const
{
	if (!faceEdgesPtr_)
	{
		calcAddressing();
	}

	return *faceEdgesPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
pointEdges() const
{
	if (!pointEdgesPtr_)
	{
		calcPointEdges();
	}

	return *pointEdgesPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
pointFaces() const
{
	if (!pointFacesPtr_)
	{
		calcPointFaces();
	}

	return *pointFacesPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::List<Face>&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
localFaces() const
{
	if (!localFacesPtr_)
	{
		calcMeshData();
	}

	return *localFacesPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::labelList&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
meshPoints() const
{
	if (!meshPointsPtr_)
	{
		calcMeshData();
	}

	return *meshPointsPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::Map<tnbLib::label>&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
meshPointMap() const
{
	if (!meshPointMapPtr_)
	{
		calcMeshPointMap();
	}

	return *meshPointMapPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::Field<PointType>&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
localPoints() const
{
	if (!localPointsPtr_)
	{
		calcLocalPoints();
	}

	return *localPointsPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::labelList&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
localPointOrder() const
{
	if (!localPointOrderPtr_)
	{
		calcLocalPointOrder();
	}

	return *localPointOrderPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
tnbLib::label
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
whichPoint
(
	const label gp
) const
{
	Map<label>::const_iterator fnd = meshPointMap().find(gp);

	if (fnd != meshPointMap().end())
	{
		return fnd();
	}
	else
	{
		// Not found
		return -1;
	}
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::Field<PointType>&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
faceCentres() const
{
	if (!faceCentresPtr_)
	{
		calcFaceCentres();
	}

	return *faceCentresPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::Field<PointType>&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
faceNormals() const
{
	if (!faceNormalsPtr_)
	{
		calcFaceNormals();
	}

	return *faceNormalsPtr_;
}


template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
const tnbLib::Field<PointType>&
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
pointNormals() const
{
	if (!pointNormalsPtr_)
	{
		calcPointNormals();
	}

	return *pointNormalsPtr_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template
<
	class Face,
	template<class> class FaceList,
	class PointField,
	class PointType
>
void
tnbLib::PrimitivePatch<Face, FaceList, PointField, PointType>::
operator=
(
	const PrimitivePatch<Face, FaceList, PointField, PointType>& pp
	)
{
	clearOut();

	FaceList<Face>::operator=(pp);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PrimitivePatchAddressing.cxx>
#include <PrimitivePatchEdgeLoops.cxx>
#include <PrimitivePatchClear.cxx>
#include <PrimitivePatchBdryPoints.cxx>
#include <PrimitivePatchLocalPointOrder.cxx>
#include <PrimitivePatchMeshData.cxx>
#include <PrimitivePatchMeshEdges.cxx>
#include <PrimitivePatchPointAddressing.cxx>
#include <PrimitivePatchProjectPoints.cxx>
#include <PrimitivePatchCheck.cxx>

// ************************************************************************* //