#include <polyMesh.hxx>

#include <mapPolyMesh.hxx>
#include <tnbTime.hxx>
#include <globalMeshData.hxx>
#include <meshObjectBase.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::polyMesh::updateMesh(const mapPolyMesh& mpm)
{
	// Update zones.  Since boundary depends on zones, they need to be
	// updated first.  HJ, 20/May/2014
	pointZones_.updateMesh();
	faceZones_.updateMesh();
	cellZones_.updateMesh();

	// Update boundaryMesh (note that patches themselves are already ok)
	boundary_.updateMesh();

	// Clear out parallel data.  HJ, 27/Nov/2009
	deleteDemandDrivenData(globalMeshDataPtr_);

	setInstance(time().timeName());

	// Map the old motion points if present
	if (oldAllPointsPtr_)
	{
		// Make a copy of the original points
		pointField oldMotionPoints = *oldAllPointsPtr_;

		pointField& newMotionPoints = *oldAllPointsPtr_;

		// Resize the list to new size
		newMotionPoints.setSize(allPoints_.size());

		// Map the list
		newMotionPoints.map(oldMotionPoints, mpm.pointMap());

		// Reset old points if present
		if (oldPointsPtr_)
		{
			oldPointsPtr_->reset(*oldAllPointsPtr_, nPoints());
		}
	}

	// Reset valid directions (could change by faces put into empty patches)
	geometricD_ = Vector<label>::zero;
	solutionD_ = Vector<label>::zero;

	// Update all function objects
	// Moved from fvMesh.C in 1.6.x merge.  HJ, 29/Aug/2010
	meshObjectBase::allUpdateTopology<polyMesh>(*this, mpm);
}


// Sync mesh update with changes on other processors
void tnbLib::polyMesh::syncUpdateMesh()
{
	// Update zones.  Since boundary depends on zones, they need to be
	// updated first.  HJ, 20/May/2014
	pointZones_.updateMesh();
	faceZones_.updateMesh();
	cellZones_.updateMesh();

	// Update boundaryMesh (note that patches themselves already ok)
	boundary_.updateMesh();

	// Clear out parallel data.  HJ, 27/Nov/2009
	deleteDemandDrivenData(globalMeshDataPtr_);

	setInstance(time().timeName());

	// Reset valid directions (could change by faces put into empty patches)
	geometricD_ = Vector<label>::zero;
	solutionD_ = Vector<label>::zero;

	// Update all function objects
	// Moved from fvMesh.C in 1.6.x merge.  HJ, 29/Aug/2010

	// Instantiate a dummy mapPolyMesh
	autoPtr<mapPolyMesh> mapPtr(new mapPolyMesh(*this));

	meshObjectBase::allUpdateTopology<polyMesh>(*this, mapPtr());
}


// ************************************************************************* //