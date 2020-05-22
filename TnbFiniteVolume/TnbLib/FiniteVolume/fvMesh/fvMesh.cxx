#include <fvMesh.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <slicedVolFields.hxx>
#include <slicedSurfaceFields.hxx>
#include <SubField.hxx>
#include <demandDrivenData.hxx>
#include <fvMeshLduAddressing.hxx>
#include <emptyPolyPatch.hxx>
#include <mapPolyMesh.hxx>
#include <MapFvFields.hxx>
#include <fvMeshMapper.hxx>
#include <mapClouds.hxx>
#include <tnbTime.hxx>

#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(tnbLib::fvMesh, 0);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fvMesh::clearGeomNotOldVol()
{
	deleteDemandDrivenData(VPtr_);

	deleteDemandDrivenData(SfPtr_);
	deleteDemandDrivenData(magSfPtr_);
	deleteDemandDrivenData(CPtr_);
	deleteDemandDrivenData(CfPtr_);
}


void tnbLib::fvMesh::clearGeom()
{
	clearGeomNotOldVol();

	deleteDemandDrivenData(V0Ptr_);
	deleteDemandDrivenData(V00Ptr_);

	// Mesh motion flux cannot be deleted here because the old-time flux
	// needs to be saved.

	// Geometry dependent object updated through call-back
	// and handled by polyMesh
	// HJ, 29/Aug/2010
}


void tnbLib::fvMesh::clearAddressing()
{
	deleteDemandDrivenData(lduPtr_);

	// Geometry dependent object updated through call-back
	// and handled by polyMesh
	// HJ, 29/Aug/2010
}


void tnbLib::fvMesh::clearOut()
{
	clearGeom();
	surfaceInterpolation::clearOut();

	clearAddressing();

	// Clear mesh motion flux
	deleteDemandDrivenData(phiPtr_);

	polyMesh::clearOut();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fvMesh::fvMesh(const IOobject& io)
	:
	polyMesh(io),
	surfaceInterpolation(*this),
	boundary_(*this, boundaryMesh()),
	lduPtr_(NULL),
	curTimeIndex_(time().timeIndex()),
	VPtr_(NULL),
	V0Ptr_(NULL),
	V00Ptr_(NULL),
	SfPtr_(NULL),
	magSfPtr_(NULL),
	CPtr_(NULL),
	CfPtr_(NULL),
	phiPtr_(NULL)
{
	if (debug)
	{
		Info << "Constructing fvMesh from IOobject"
			<< endl;
	}

	// Check the existance of the cell volumes and read if present
	// and set the storage of V00
	if (isFile(time().timePath() / "V0"))
	{
		if (debug)
		{
			Info << "Reading old cell volumes" << endl;
		}

		V0Ptr_ = new DimensionedField<scalar, volMesh>
			(
				IOobject
				(
					"V0",
					time().timeName(),
					*this,
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				),
				*this
				);

		V00();
	}

	// Check the existance of the mesh fluxes, read if present and set the
	// mesh to be moving
	if (isFile(time().timePath() / "meshPhi"))
	{
		if (debug)
		{
			Info << "Reading motion fluxes" << endl;
		}

		phiPtr_ = new surfaceScalarField
		(
			IOobject
			(
				"meshPhi",
				time().timeName(),
				*this,
				IOobject::MUST_READ,
				IOobject::AUTO_WRITE
			),
			*this
		);

		// The mesh is now considered moving so the old-time cell volumes
		// will be required for the time derivatives so if they haven't been
		// read initialise to the current cell volumes
		if (!V0Ptr_)
		{
			V0Ptr_ = new DimensionedField<scalar, volMesh>
				(
					IOobject
					(
						"V0",
						time().timeName(),
						*this,
						IOobject::NO_READ,
						IOobject::NO_WRITE,
						false
					),
					V()
					);
		}

		moving(true);
	}
}


tnbLib::fvMesh::fvMesh
(
	const IOobject& io,
	const Xfer<pointField>& points,
	const Xfer<faceList>& faces,
	const Xfer<labelList>& allOwner,
	const Xfer<labelList>& allNeighbour,
	const bool syncPar
)
	:
	polyMesh(io, points, faces, allOwner, allNeighbour, syncPar),
	surfaceInterpolation(*this),
	boundary_(*this),
	lduPtr_(NULL),
	curTimeIndex_(time().timeIndex()),
	VPtr_(NULL),
	V0Ptr_(NULL),
	V00Ptr_(NULL),
	SfPtr_(NULL),
	magSfPtr_(NULL),
	CPtr_(NULL),
	CfPtr_(NULL),
	phiPtr_(NULL)
{
	if (debug)
	{
		Info << "Constructing fvMesh from components" << endl;
	}
}


tnbLib::fvMesh::fvMesh
(
	const IOobject& io,
	const Xfer<pointField>& points,
	const Xfer<faceList>& faces,
	const Xfer<cellList>& cells,
	const bool syncPar
)
	:
	polyMesh(io, points, faces, cells, syncPar),
	surfaceInterpolation(*this),
	boundary_(*this),
	lduPtr_(NULL),
	curTimeIndex_(time().timeIndex()),
	VPtr_(NULL),
	V0Ptr_(NULL),
	V00Ptr_(NULL),
	SfPtr_(NULL),
	magSfPtr_(NULL),
	CPtr_(NULL),
	CfPtr_(NULL),
	phiPtr_(NULL)
{
	if (debug)
	{
		Info << "Constructing fvMesh from components" << endl;
	}
}


tnbLib::fvMesh::fvMesh
(
	const IOobject& io,
	const Xfer<pointField>& points,
	const cellShapeList& shapes,
	const faceListList& boundaryFaces,
	const wordList& boundaryPatchNames,
	const wordList& boundaryPatchTypes,
	const word& defaultBoundaryPatchName,
	const word& defaultBoundaryPatchType,
	const wordList& boundaryPatchPhysicalTypes,
	const bool syncPar
)
	:
	polyMesh
	(
		io,
		points,
		shapes,
		boundaryFaces,
		boundaryPatchNames,
		boundaryPatchTypes,
		defaultBoundaryPatchName,
		defaultBoundaryPatchType,
		boundaryPatchPhysicalTypes,
		syncPar
	),
	surfaceInterpolation(*this),
	boundary_(*this),
	lduPtr_(NULL),
	curTimeIndex_(time().timeIndex()),
	VPtr_(NULL),
	V0Ptr_(NULL),
	V00Ptr_(NULL),
	SfPtr_(NULL),
	magSfPtr_(NULL),
	CPtr_(NULL),
	CfPtr_(NULL),
	phiPtr_(NULL)
{
	if (debug)
	{
		Info << "Constructing fvMesh from components" << endl;
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fvMesh::~fvMesh()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fvMesh::addFvPatches
(
	const List<polyPatch*> & p,
	const bool validBoundary
)
{
	if (boundary().size())
	{
		FatalErrorIn
		(
			"fvMesh::addFvPatches(const List<polyPatch*>&, const bool)"
		) << " boundary already exists"
			<< abort(FatalError);
	}

	// first add polyPatches
	addPatches(p, validBoundary);
	boundary_.addPatches(boundaryMesh());
}


void tnbLib::fvMesh::removeFvBoundary()
{
	if (debug)
	{
		Info << "void fvMesh::removeFvBoundary(): "
			<< "Removing boundary patches."
			<< endl;
	}

	// Remove fvBoundaryMesh data first.
	boundary_.clear();
	boundary_.setSize(0);
	polyMesh::removeBoundary();

	clearOut();
}


tnbLib::polyMesh::readUpdateState tnbLib::fvMesh::readUpdate()
{
	if (debug)
	{
		Info << "polyMesh::readUpdateState fvMesh::readUpdate() : "
			<< "Updating fvMesh.  ";
	}

	// Note: issues with update: should meshObject update happen
	// in polyMesh or fvMesh?  HJ, 18/Feb/2011
	polyMesh::readUpdateState state = polyMesh::readUpdate();

	if (state == polyMesh::TOPO_PATCH_CHANGE)
	{
		if (debug)
		{
			Info << "Boundary and topological update" << endl;
		}

		boundary_.readUpdate(boundaryMesh());

		clearOut();

	}
	else if (state == polyMesh::TOPO_CHANGE)
	{
		if (debug)
		{
			Info << "Topological update" << endl;
		}

		clearOut();
	}
	else if (state == polyMesh::POINTS_MOVED)
	{
		if (debug)
		{
			Info << "Point motion update" << endl;
		}

		clearGeom();
	}
	else
	{
		if (debug)
		{
			Info << "No update" << endl;
		}
	}

	return state;
}


const tnbLib::fvBoundaryMesh& tnbLib::fvMesh::boundary() const
{
	return boundary_;
}


const tnbLib::lduAddressing& tnbLib::fvMesh::lduAddr() const
{
	if (!lduPtr_)
	{
		lduPtr_ = new fvMeshLduAddressing(*this);
	}

	return *lduPtr_;
}


void tnbLib::fvMesh::mapFields(const mapPolyMesh& meshMap) const
{
	if (debug)
	{
		Info << "void fvMesh::mapFields(const mapPolyMesh& meshMap) const: "
			<< "Mapping fv fields."
			<< endl;
	}

	// Create a mapper
	const fvMeshMapper mapper(*this, meshMap);

	// Map all the volFields in the objectRegistry
	MapGeometricFields<scalar, fvPatchField, fvMeshMapper, volMesh>(mapper);
	MapGeometricFields<vector, fvPatchField, fvMeshMapper, volMesh>(mapper);
	MapGeometricFields<sphericalTensor, fvPatchField, fvMeshMapper, volMesh>
		(mapper);

	MapGeometricFields<symmTensor, fvPatchField, fvMeshMapper, volMesh>
		(mapper);

	MapGeometricFields<symmTensor4thOrder, fvPatchField, fvMeshMapper, volMesh>
		(mapper);

	MapGeometricFields<diagTensor, fvPatchField, fvMeshMapper, volMesh>
		(mapper);

	MapGeometricFields<tensor, fvPatchField, fvMeshMapper, volMesh>(mapper);

	// Map all the surfaceFields in the objectRegistry
	MapGeometricFields<scalar, fvsPatchField, fvMeshMapper, surfaceMesh>
		(mapper);

	MapGeometricFields<vector, fvsPatchField, fvMeshMapper, surfaceMesh>
		(mapper);

	MapGeometricFields
		<sphericalTensor, fvsPatchField, fvMeshMapper, surfaceMesh>(mapper);
	MapGeometricFields<symmTensor, fvsPatchField, fvMeshMapper, surfaceMesh>
		(mapper);

	MapGeometricFields<symmTensor4thOrder, fvsPatchField, fvMeshMapper, surfaceMesh>
		(mapper);

	MapGeometricFields<diagTensor, fvsPatchField, fvMeshMapper, surfaceMesh>
		(mapper);

	MapGeometricFields<tensor, fvsPatchField, fvMeshMapper, surfaceMesh>
		(mapper);

	// Map all the clouds in the objectRegistry
	mapClouds(*this, meshMap);
}


void tnbLib::fvMesh::mapOldVolumes(const mapPolyMesh& meshMap)
{
	const labelList& cellMap = meshMap.cellMap();

	// Map the old volume. Just map to new cell labels.
	if (V0Ptr_)
	{
		if (debug)
		{
			InfoIn("void fvMesh::mapOldVolumes(const mapPolyMesh& meshMap)")
				<< "Mapping old cell volumes." << endl;
		}

		scalarField& V0 = *V0Ptr_;

		scalarField savedV0(V0);
		V0.setSize(nCells());

		forAll(V0, i)
		{
			if (cellMap[i] > -1)
			{
				V0[i] = savedV0[cellMap[i]];
			}
			else
			{
				V0[i] = 0.0;
			}
		}
	}

	// Map the old-old volume. Just map to new cell labels.
	if (V00Ptr_)
	{
		if (debug)
		{
			InfoIn("void fvMesh::mapOldVolumes(const mapPolyMesh& meshMap)")
				<< "Mapping old-old cell volumes." << endl;
		}

		scalarField& V00 = *V00Ptr_;

		scalarField savedV00(V00);
		V00.setSize(nCells());

		forAll(V00, i)
		{
			if (cellMap[i] > -1)
			{
				V00[i] = savedV00[cellMap[i]];
			}
			else
			{
				V00[i] = 0.0;
			}
		}
	}
}


void tnbLib::fvMesh::updateMesh(const mapPolyMesh& mpm)
{
	// Update polyMesh. This needs to keep volume existent!
	polyMesh::updateMesh(mpm);

	surfaceInterpolation::clearOut();
	clearGeomNotOldVol();

	// Map all fields
	mapFields(mpm);

	// Map old-volumes
	mapOldVolumes(mpm);

	clearAddressing();

	// Mesh morphing should also clear out the surfaceInterpolation.
	// This is a temporary solution
	surfaceInterpolation::movePoints();

	// Function object update moved to polyMesh
	// HJ, 29/Aug/2010
}


void tnbLib::fvMesh::syncUpdateMesh()
{
	// Update polyMesh. This needs to keep volume existent!
	polyMesh::syncUpdateMesh();

	// Not sure how much clean-up is needed here.  HJ, 27/Nov/2009

	surfaceInterpolation::clearOut();
	clearGeomNotOldVol();

	clearAddressing();

	// handleMorph() should also clear out the surfaceInterpolation.
	// This is a temporary solution
	surfaceInterpolation::movePoints();

	// Function object update moved to polyMesh
	// HJ, 29/Aug/2010
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::fvMesh::movePoints(const pointField& p)
{
	// Grab old time volumes if the time has been incremented
	if (curTimeIndex_ < time().timeIndex())
	{
		if (V00Ptr_ && V0Ptr_)
		{
			if (debug)
			{
				InfoIn("void fvMesh::movePoints(const pointField& p)")
					<< "Grabbing old-old cell volumes." << endl;
			}

			*V00Ptr_ = *V0Ptr_;
		}

		if (V0Ptr_)
		{
			if (debug)
			{
				InfoIn("void fvMesh::movePoints(const pointField& p)")
					<< "Grabbing old cell volumes." << endl;
			}

			*V0Ptr_ = V();
		}
		else
		{
			if (debug)
			{
				InfoIn("void fvMesh::movePoints(const pointField& p)")
					<< "Creating old cell volumes." << endl;
			}

			V0Ptr_ = new DimensionedField<scalar, volMesh>
				(
					IOobject
					(
						"V0",
						time().timeName(),
						*this,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					V()
					);
		}

		curTimeIndex_ = time().timeIndex();
	}


	// Delete out of date geometrical information
	clearGeomNotOldVol();


	if (!phiPtr_)
	{
		// Create mesh motion flux
		if (debug)
		{
			InfoIn("tmp<scalarField> fvMesh::movePoints(const pointField& p)")
				<< "Creating new mesh motion fluxes" << endl;
		}

		phiPtr_ = new surfaceScalarField
		(
			IOobject
			(
				"meshPhi",
				this->time().timeName(),
				*this,
				IOobject::NO_READ,
				IOobject::AUTO_WRITE
			),
			*this,
			dimVolume / dimTime
		);
	}
	else
	{
		// Grab old time mesh motion fluxes if the time has been incremented
		if (phiPtr_->timeIndex() < time().timeIndex())
		{
			phiPtr_->oldTime();
		}
	}

	// Move the polyMesh and set the mesh motion fluxes to the swept-volumes
	tmp<scalarField> tsweptVols = polyMesh::movePoints(p);

	updatePhi(tsweptVols());

	boundary_.movePoints();
	surfaceInterpolation::movePoints();

	// Function object update moved to polyMesh
	// HJ, 29/Aug/2010

	return tsweptVols;
}


bool tnbLib::fvMesh::writeObjects
(
	IOstream::streamFormat fmt,
	IOstream::versionNumber ver,
	IOstream::compressionType cmp
) const
{
	return polyMesh::writeObject(fmt, ver, cmp);
}


//- Write mesh using IO settings from the time
bool tnbLib::fvMesh::write() const
{
	return polyMesh::write();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

bool tnbLib::fvMesh::operator!=(const fvMesh& bm) const
{
	return &bm != this;
}


bool tnbLib::fvMesh::operator==(const fvMesh& bm) const
{
	return &bm == this;
}


// ************************************************************************* //