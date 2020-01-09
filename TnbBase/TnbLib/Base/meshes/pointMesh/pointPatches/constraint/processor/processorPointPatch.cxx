#include <processorPointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <globalPointPatch.hxx>
#include <faceList.hxx>
#include <primitiveFacePatch.hxx>
#include <emptyPolyPatch.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(processorPointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		processorPointPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

	void tnbLib::processorPointPatch::initGeometry()
	{
		// Algorithm:
		// Depending on whether the patch is a master or a slave, get the primitive
		// patch points and filter away the points from the global patch.

		if (isMaster())
		{
			meshPoints_ = procPolyPatch_.meshPoints();
		}
		else
		{
			// Slave side.  Create the reversed patch and pick up its points
			// so that the order is correct
			const polyPatch& pp = patch();

			faceList masterFaces(pp.size());

			forAll(pp, faceI)
			{
				masterFaces[faceI] = pp[faceI].reverseFace();
			}

			meshPoints_ = primitiveFacePatch
			(
				masterFaces,
				pp.points()
			).meshPoints();
		}
	}


	void tnbLib::processorPointPatch::calcGeometry()
	{}


	void processorPointPatch::initUpdateMesh()
	{
		facePointPatch::initUpdateMesh();
		processorPointPatch::initGeometry();
	}


	void processorPointPatch::updateMesh()
	{
		facePointPatch::updateMesh();
		processorPointPatch::calcGeometry();
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	processorPointPatch::processorPointPatch
	(
		const polyPatch& patch,
		const pointBoundaryMesh& bm
	)
		:
		coupledFacePointPatch(patch, bm),
		procPolyPatch_(refCast<const processorPolyPatch>(patch)),
		meshPoints_()
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	processorPointPatch::~processorPointPatch()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const labelList& processorPointPatch::meshPoints() const
	{
		return meshPoints_;
	}


	const pointField& processorPointPatch::localPoints() const
	{
		notImplemented("processorPointPatch::localPoints() const");
		return Field<point>::null();
	}


	const vectorField& processorPointPatch::pointNormals() const
	{
		notImplemented("processorPointPatch::pointNormals() const");
		return Field<vector>::null();
	}


	const labelList& processorPointPatch::localEdgeIndices() const
	{
		notImplemented("processorPointPatch::localEdgeIndices() const");
		return labelList::null();
	}


	const labelList& processorPointPatch::cutEdgeIndices() const
	{
		notImplemented("processorPointPatch::cutEdgeIndices() const");
		return labelList::null();
	}


	const labelList& processorPointPatch::cutEdgeOwnerIndices() const
	{
		notImplemented
		(
			"processorPointPatch::cutEdgeOwnerIndices() const"
		);
		return labelList::null();
	}


	const labelList& processorPointPatch::cutEdgeOwnerStart() const
	{
		notImplemented("processorPointPatch::cutEdgeOwnerStart() const");
		return labelList::null();
	}


	const labelList& processorPointPatch::
		cutEdgeNeighbourIndices() const
	{
		notImplemented("processorPointPatch::cutEdgeNeighbourIndices() const");
		return labelList::null();
	}


	const labelList& processorPointPatch::cutEdgeNeighbourStart() const
	{
		notImplemented("processorPointPatch::cutEdgeNeighbourStart() const");
		return labelList::null();
	}


	const labelList& processorPointPatch::doubleCutEdgeIndices() const
	{
		notImplemented("processorPointPatch::doubleCutEdgeIndices() const");
		return labelList::null();
	}


	const labelList& processorPointPatch::doubleCutOwner() const
	{
		notImplemented("processorPointPatch::doubleCutOwner() const");
		return labelList::null();
	}


	const labelList& processorPointPatch::doubleCutNeighbour() const
	{
		notImplemented("processorPointPatch::doubleCutNeighbour() const");
		return labelList::null();
	}


	const scalarField& processorPointPatch::ownNeiDoubleMask() const
	{
		notImplemented("processorPointPatch::ownNeiDoubleMask() const");
		return scalarField::null();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //