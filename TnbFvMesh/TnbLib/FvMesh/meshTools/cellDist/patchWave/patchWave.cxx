#include <patchWave.hxx>

#include <polyMesh.hxx>
#include <wallPoint.hxx>
#include <MeshWave.hxx>
#include <globalMeshData.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::patchWave::setChangedFaces
(
	const labelHashSet& patchIDs,
	labelList& changedFaces,
	List<wallPoint>& faceDist
) const
{
	const polyMesh& mesh = cellDistFuncs::mesh();

	label nChangedFaces = 0;

	forAll(mesh.boundaryMesh(), patchI)
	{
		if (patchIDs.found(patchI))
		{
			const polyPatch& patch = mesh.boundaryMesh()[patchI];

			forAll(patch.faceCentres(), patchFaceI)
			{
				label meshFaceI = patch.start() + patchFaceI;

				changedFaces[nChangedFaces] = meshFaceI;

				faceDist[nChangedFaces] =
					wallPoint
					(
						patch.faceCentres()[patchFaceI],
						0.0
					);

				nChangedFaces++;
			}
		}
	}
}


tnbLib::label tnbLib::patchWave::getValues(const MeshWave<wallPoint>& waveInfo)
{
	const List<wallPoint>& cellInfo = waveInfo.allCellInfo();
	const List<wallPoint>& faceInfo = waveInfo.allFaceInfo();

	label nIllegal = 0;

	// Copy cell values
	distance_.setSize(cellInfo.size());

	forAll(cellInfo, cellI)
	{
		scalar dist = cellInfo[cellI].distSqr();

		if (cellInfo[cellI].valid())
		{
			distance_[cellI] = tnbLib::sqrt(dist);
		}
		else
		{
			distance_[cellI] = dist;

			nIllegal++;
		}
	}

	// Copy boundary values
	forAll(patchDistance_, patchI)
	{
		const polyPatch& patch = mesh().boundaryMesh()[patchI];

		// Allocate storage for patchDistance
		scalarField* patchDistPtr = new scalarField(patch.size());

		patchDistance_.set(patchI, patchDistPtr);

		scalarField& patchField = *patchDistPtr;

		forAll(patchField, patchFaceI)
		{
			label meshFaceI = patch.start() + patchFaceI;

			scalar dist = faceInfo[meshFaceI].distSqr();

			if (faceInfo[meshFaceI].valid())
			{
				// Adding SMALL to avoid problems with /0 in the turbulence
				// models
				patchField[patchFaceI] = tnbLib::sqrt(dist) + SMALL;
			}
			else
			{
				patchField[patchFaceI] = dist;

				nIllegal++;
			}
		}
	}

	return nIllegal;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::patchWave::patchWave
(
	const polyMesh& mesh,
	const labelHashSet& patchIDs,
	const bool correctWalls
)
	:
	cellDistFuncs(mesh),
	patchIDs_(patchIDs),
	correctWalls_(correctWalls),
	nUnset_(0),
	distance_(mesh.nCells()),
	patchDistance_(mesh.boundaryMesh().size())
{
	patchWave::correct();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::patchWave::~patchWave()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Correct for mesh geom/topo changes. Might be more intelligent in the
// future (if only small topology change)
void tnbLib::patchWave::correct()
{
	//
	// Set initial changed faces: set wallPoint for wall faces to wall centre
	//

	// Count walls
	label nWalls = sumPatchSize(patchIDs_);

	List<wallPoint> faceDist(nWalls);
	labelList changedFaces(nWalls);

	// Set to faceDist information to facecentre on walls.
	setChangedFaces(patchIDs_, changedFaces, faceDist);


	//
	// Do calculate wall distance by 'growing' from faces.
	//

	MeshWave<wallPoint> waveInfo
	(
		mesh(),
		changedFaces,
		faceDist,
		mesh().globalData().nTotalCells()   // max iterations
	);


	//
	// Copy distance into return field
	//

	nUnset_ = getValues(waveInfo);

	//
	// Correct wall cells for true distance
	//

	if (correctWalls_)
	{
		Map<label> nearestFace(2 * nWalls);

		correctBoundaryFaceCells
		(
			patchIDs_,
			distance_,
			nearestFace
		);

		correctBoundaryPointCells
		(
			patchIDs_,
			distance_,
			nearestFace
		);
	}
}


// ************************************************************************* //