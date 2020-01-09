#include <globalPointPatch.hxx>

#include <triFaceList.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::globalPointPatch, 0);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::globalPointPatch::globalPointPatch
(
	const pointBoundaryMesh& bm,
	const label index
)
	:
	pointPatch(bm),
	coupledPointPatch(bm),
	index_(index)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::globalPointPatch::~globalPointPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::triFaceList tnbLib::globalPointPatch::faceTriangles
(
	const label
) const
{
	notImplemented
	(
		"processorPointPatch::faceTriangles(label faceID) const"
	);

	return triFaceList::null();
}


const tnbLib::edgeList& tnbLib::globalPointPatch::meshEdges() const
{
	notImplemented("globalPointPatch::meshEdges() const");
	return edgeList::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::sharedEdgeAddr() const
{
	notImplemented("globalPointPatch::sharedEdgeAddr() const");
	return labelList::null();
}


const tnbLib::edgeList& tnbLib::globalPointPatch::meshCutEdges() const
{
	notImplemented("globalPointPatch::meshCutEdges() const");
	return edgeList::null();
}


const tnbLib::scalarField& tnbLib::globalPointPatch::meshCutEdgeMask() const
{
	notImplemented("globalPointPatch::meshCutEdgeMask() const");
	return scalarField::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::localEdgeIndices() const
{
	notImplemented("globalPointPatch::localEdgeIndices() const");
	return labelList::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::cutEdgeIndices() const
{
	notImplemented("globalPointPatch::cutEdgeIndices() const");
	return labelList::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::cutEdgeOwnerIndices() const
{
	notImplemented("globalPointPatch::cutEdgeOwnerIndices() const");
	return labelList::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::cutEdgeOwnerStart() const
{
	notImplemented("globalPointPatch::cutEdgeOwnerStart() const");
	return labelList::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::cutEdgeNeighbourIndices() const
{
	notImplemented
	(
		"globalPointPatch::cutEdgeNeighbourIndices() const"
	);
	return labelList::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::cutEdgeNeighbourStart() const
{
	notImplemented("globalPointPatch::cutEdgeNeighbourStart() const");
	return labelList::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::doubleCutEdgeIndices() const
{
	notImplemented("globalPointPatch::doubleCutEdgeIndices() const");
	return labelList::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::doubleCutOwner() const
{
	notImplemented("globalPointPatch::doubleCutOwner() const");
	return labelList::null();
}


const tnbLib::labelList& tnbLib::globalPointPatch::doubleCutNeighbour() const
{
	notImplemented("globalPointPatch::doubleCutNeighbour() const");
	return labelList::null();
}


const tnbLib::scalarField& tnbLib::globalPointPatch::ownNeiDoubleMask() const
{
	notImplemented("globalPointPatch::ownNeiDoubleMask() const");
	return scalarField::null();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //