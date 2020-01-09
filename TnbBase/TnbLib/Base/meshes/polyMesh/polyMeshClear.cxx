#include <polyMesh.hxx>

#include <primitiveMesh.hxx>
#include <globalMeshData.hxx>
#include <demandDrivenData.hxx>
#include <meshObjectBase.hxx>
#include <pointMesh.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::polyMesh::removeBoundary()
{
	if (debug)
	{
		Info << "void polyMesh::removeBoundary(): "
			<< "Removing boundary patches."
			<< endl;
	}

	// Remove the point zones
	boundary_.clear();
	boundary_.setSize(0);

	clearOut();
}


void tnbLib::polyMesh::removeZones()
{
	if (debug)
	{
		Info << "void polyMesh::removeZones(): "
			<< "Removing point, face and cell zones."
			<< endl;
	}

	// Remove the zones and reset writing
	pointZones_.clear();
	pointZones_.setSize(0);
	pointZones_.writeOpt() = IOobject::NO_WRITE;

	faceZones_.clear();
	faceZones_.setSize(0);
	faceZones_.writeOpt() = IOobject::NO_WRITE;

	cellZones_.clear();
	cellZones_.setSize(0);
	cellZones_.writeOpt() = IOobject::NO_WRITE;
	clearOut();
}


void tnbLib::polyMesh::clearGeom()
{
	if (debug)
	{
		Info << "void polyMesh::clearGeom() : "
			<< "clearing geometric data"
			<< endl;
	}

	primitiveMesh::clearGeom();

	forAll(boundary_, patchI)
	{
		boundary_[patchI].clearGeom();
	}

	// Reset valid directions (could change with rotation)
	geometricD_ = Vector<label>::zero;
	solutionD_ = Vector<label>::zero;

	// Move points all mesh objects.  HJ, 13/Oct/2010
	// This is a problem, because it is called in a destructor.
	meshObjectBase::allDelete(*this);
	//     meshObjectBase::allMovePoints(*this);
}


void tnbLib::polyMesh::clearAddressing()
{
	if (debug)
	{
		Info << "void polyMesh::clearAddressing() : "
			<< "clearing topology"
			<< endl;
	}

	primitiveMesh::clearAddressing();

	// parallelData depends on the processorPatch ordering so force
	// recalculation
	deleteDemandDrivenData(globalMeshDataPtr_);

	// Reset valid directions
	geometricD_ = Vector<label>::zero;
	solutionD_ = Vector<label>::zero;
}


void tnbLib::polyMesh::clearPrimitives()
{
	resetMotion();

	allPoints_.setSize(0);
	allFaces_.setSize(0);
	owner_.setSize(0);
	neighbour_.setSize(0);

	clearedPrimitives_ = true;
}


void tnbLib::polyMesh::clearOut()
{
	clearGeom();
	clearAddressing();
}


// ************************************************************************* //