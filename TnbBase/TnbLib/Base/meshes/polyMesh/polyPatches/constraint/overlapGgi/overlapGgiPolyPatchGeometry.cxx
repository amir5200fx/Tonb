#include <overlapGgiPolyPatch.hxx>

#include <polyPatch.hxx>
#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <demandDrivenData.hxx>
#include <polyPatchID.hxx>
#include <OFstream.hxx>
#include <tnbTime.hxx>
#include <OStringStream.hxx>
#include <RodriguesRotation.hxx>
#include <transformField.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Create expanded patch
tnbLib::standAlonePatch*
tnbLib::overlapGgiPolyPatch::calcExpandedGeometry(label ncp, label index) const
{
	const scalar myAngle = 360.0 / scalar(ncp);

	// Create expanded master points and faces
	const faceZone& geomZone = boundaryMesh().mesh().faceZones()[index];
	const primitiveFacePatch& geom = geomZone();

	const pointField& geomLocalPoints = geom.localPoints();

	pointField expandedPoints(ncp*geomLocalPoints.size());

	// Transform points
	label nPointsGeom = 0;

	for (label copyI = 0; copyI < ncp; copyI++)
	{
		// Calculate transform
		const tensor curRotation =
			RodriguesRotation(rotationAxis_, copyI*myAngle);

		forAll(geomLocalPoints, pointI)
		{
			expandedPoints[nPointsGeom] =
				transform(curRotation, geomLocalPoints[pointI]);
			nPointsGeom++;
		}
	}

	// Transform faces
	const faceList& geomLocalFaces = geom.localFaces();
	faceList expandedFaces(ncp*geomLocalFaces.size());

	label nFacesGeom = 0;

	for (label copyI = 0; copyI < ncp; copyI++)
	{
		const label copyOffsetGeom = copyI * geomLocalPoints.size();

		forAll(geomLocalFaces, faceI)
		{
			const face& curGeomFace = geomLocalFaces[faceI];

			face& curExpandedFace = expandedFaces[nFacesGeom];

			// Copy face with offsets
			curExpandedFace.setSize(curGeomFace.size());

			forAll(curGeomFace, fpI)
			{
				curExpandedFace[fpI] = curGeomFace[fpI] + copyOffsetGeom;
			}

			nFacesGeom++;
		}
	}

	if (debug > 1)
	{
		Info << "Writing expanded geom patch as VTK" << endl;

		const polyMesh& mesh = boundaryMesh().mesh();

		fileName fvPath(mesh.time().path() / "VTK");
		mkDir(fvPath);

		OStringStream outputFilename;
		outputFilename << "expandedGeom" << name() << shadow().name()
			<< index << "_" << mesh.time().timeName();

		standAlonePatch::writeVTK
		(
			fvPath / fileName(outputFilename.str()),
			expandedFaces,
			expandedPoints
		);
	}

	return new standAlonePatch(expandedFaces, expandedPoints);
}


const tnbLib::standAlonePatch& tnbLib::overlapGgiPolyPatch::expandedMaster() const
{
	if (!expandedMasterPtr_)
	{
		expandedMasterPtr_ = calcExpandedGeometry(nCopies(), zoneIndex());
	}

	return *expandedMasterPtr_;
}


const tnbLib::standAlonePatch& tnbLib::overlapGgiPolyPatch::expandedSlave() const
{
	if (!expandedSlavePtr_)
	{
		expandedSlavePtr_ =
			calcExpandedGeometry(shadow().nCopies(), shadow().zoneIndex());
	}

	return *expandedSlavePtr_;
}


void tnbLib::overlapGgiPolyPatch::calcPatchToPatch() const
{
	// Create patch-to-patch interpolation between the expanded master
	// and slave patches
	if (patchToPatchPtr_)
	{
		FatalErrorIn("void overlapGgiPolyPatch::calcPatchToPatch() const")
			<< "Patch to patch interpolation already calculated"
			<< abort(FatalError);
	}

	if (master())
	{
		patchToPatchPtr_ =
			new overlapGgiInterpolation
			(
				expandedMaster(),
				expandedSlave(),
				forwardT(),
				reverseT(),
				separation(),
				true,          // Patch data is complete on all processors
				SMALL,         // master overlap tolerance
				SMALL,         // slave overlap tolerance
				true,          // Rescale weighting factors.  Bug fix, MB.
				overlapGgiInterpolation::BB_OCTREE  // Octree search, MB.

			);

		// Abort immediatly if uncovered faces are present
		if
			(
				patchToPatch().uncoveredMasterFaces().size() > 0
				|| patchToPatch().uncoveredSlaveFaces().size() > 0
				)
		{
			FatalErrorIn("void overlapGgiPolyPatch::calcPatchToPatch() const")
				<< "Found uncovered faces for GGI interface "
				<< name() << "/" << shadowName() << endl
				<< "This is an unrecoverable error. Aborting."
				<< abort(FatalError);
		}
	}
	else
	{
		FatalErrorIn("void overlapGgiPolyPatch::calcPatchToPatch() const")
			<< "Attempting to create GGIInterpolation on a shadow"
			<< abort(FatalError);
	}
}


const tnbLib::overlapGgiInterpolation&
tnbLib::overlapGgiPolyPatch::patchToPatch() const
{
	if (master())
	{
		if (!patchToPatchPtr_)
		{
			if (debug)
			{
				Info << "Initializing the GGI interpolator between "
					<< "master/shadow patches: "
					<< name() << "/" << shadowName()
					<< endl;
			}

			calcPatchToPatch();
		}

		return *patchToPatchPtr_;
	}
	else
	{
		return shadow().patchToPatch();
	}
}


void tnbLib::overlapGgiPolyPatch::calcReconFaceCellCentres() const
{
	if (reconFaceCellCentresPtr_)
	{
		FatalErrorIn
		(
			"void overlapGgiPolyPatch::calcReconFaceCellCentres() const"
		) << "Reconstructed cell centres already calculated"
			<< abort(FatalError);
	}

	// Create neighbouring face centres using interpolation
	if (master())
	{
		const label shadowID = shadowIndex();

		// Get the transformed and interpolated shadow face cell centers
		reconFaceCellCentresPtr_ =
			new vectorField
			(
				interpolate
				(
					boundaryMesh()[shadowID].faceCellCentres()
					- boundaryMesh()[shadowID].faceCentres()
				)
				+ faceCentres()
			);
	}
	else
	{
		FatalErrorIn
		(
			"void overlapGgiPolyPatch::calcReconFaceCellCentres() const"
		) << "Attempting to create reconFaceCellCentres on a shadow"
			<< abort(FatalError);
	}
}


void tnbLib::overlapGgiPolyPatch::checkDefinition() const
{
	// Sanity checks
	// 1. Check
	Info << "overlapGgiPolyPatch: sanity checks missing.  HJ" << endl;

	//     if
	//     (
	//         (rotationAngle() - shadow().rotationAngle()) > SMALL
	//      || cmptSum(rotationAxis() - shadow().rotationAxis()) > SMALL
	//     )
	//     {
	//         FatalErrorIn("overlapGgiPolyPatch::patchToPatch")
	//             << "    The rotation angle for patch name           : "
	//             << name() << " is: " << rotationAngle() << " axis: "
	//             << shadow().rotationAxis() << nl
	//             << "    The rotation angle for the shadow patch name: "
	//             << shadowName() << " is: "
	//             << shadow().rotationAngle() << " axis: "
	//             << shadow().rotationAxis() << nl
	//             << "    Both values need to be the same in "
	//             << "the boundary file "
	//             << abort(FatalError);
	//     }
}


void tnbLib::overlapGgiPolyPatch::clearGeom() const
{
	// Note: Currently deleting patch-to-patch interpolation together with
	// expanded master and slave patches on mesh motion to avoid problems
	// with motion of points in primitive patch.
	// HJ, 4/Jul/2011
	deleteDemandDrivenData(expandedMasterPtr_);
	deleteDemandDrivenData(expandedSlavePtr_);

	deleteDemandDrivenData(patchToPatchPtr_);

	deleteDemandDrivenData(reconFaceCellCentresPtr_);
}


void tnbLib::overlapGgiPolyPatch::clearOut() const
{
	clearGeom();

	deleteDemandDrivenData(localParallelPtr_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::vectorField&
tnbLib::overlapGgiPolyPatch::reconFaceCellCentres() const
{
	if (!reconFaceCellCentresPtr_)
	{
		calcReconFaceCellCentres();
	}

	return *reconFaceCellCentresPtr_;
}


void tnbLib::overlapGgiPolyPatch::initAddressing()
{
	if (active())
	{
		// Calculate transforms for correct GGI interpolator cut
		calcTransforms();
		localParallel();
	}

	polyPatch::initAddressing();
}


void tnbLib::overlapGgiPolyPatch::calcAddressing()
{
	polyPatch::calcAddressing();
}


void tnbLib::overlapGgiPolyPatch::initGeometry()
{
	// Communication is allowed either before or after processor
	// patch comms.  HJ, 11/Jul/2011
	if (active())
	{
		// Note: Only master calculates recon; slave uses master interpolation
		if (master())
		{
			reconFaceCellCentres();
		}
	}

	polyPatch::initGeometry();
}


void tnbLib::overlapGgiPolyPatch::calcGeometry()
{
	polyPatch::calcGeometry();
}


void tnbLib::overlapGgiPolyPatch::initMovePoints(const pointField& p)
{
	clearGeom();

	// Calculate transforms on mesh motion?
	calcTransforms();

	if (master())
	{
		shadow().clearGeom();
		shadow().calcTransforms();
	}

	// Update interpolation for new relative position of GGI interfaces
	// Note: currently, patches and interpolation are cleared in clearGeom()
	// HJ. 4/Jul/2011
//     if (patchToPatchPtr_)
//     {
//         patchToPatchPtr_->movePoints();
//     }

	if (active() && master())
	{
		reconFaceCellCentres();
	}

	polyPatch::initMovePoints(p);
}


void tnbLib::overlapGgiPolyPatch::movePoints(const pointField& p)
{
	polyPatch::movePoints(p);
}


void tnbLib::overlapGgiPolyPatch::initUpdateMesh()
{
	polyPatch::initUpdateMesh();
}


void tnbLib::overlapGgiPolyPatch::updateMesh()
{
	polyPatch::updateMesh();
	clearOut();
}


void tnbLib::overlapGgiPolyPatch::calcTransforms() const
{
	forwardT_.setSize(0);
	reverseT_.setSize(0);
	separation_.setSize(0);
}


void tnbLib::overlapGgiPolyPatch::initOrder(const primitivePatch& pp) const
{}


bool tnbLib::overlapGgiPolyPatch::order
(
	const primitivePatch& pp,
	labelList& faceMap,
	labelList& rotation
) const
{
	faceMap.setSize(pp.size(), -1);
	rotation.setSize(pp.size(), 0);

	// Nothing changes
	return false;
}


void tnbLib::overlapGgiPolyPatch::syncOrder() const
{}


// ************************************************************************* //