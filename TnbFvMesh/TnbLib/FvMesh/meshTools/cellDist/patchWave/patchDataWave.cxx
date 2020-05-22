#include <patchDataWave.hxx>

#include <MeshWave.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Set initial set of changed faces (= all wall faces)
template<class TransferType>
void tnbLib::patchDataWave<TransferType>::setChangedFaces
(
	const labelHashSet& patchIDs,
	labelList& changedFaces,
	List<TransferType>& faceDist
) const
{
	const polyMesh& mesh = cellDistFuncs::mesh();

	label nChangedFaces = 0;

	forAll(mesh.boundaryMesh(), patchI)
	{
		if (patchIDs.found(patchI))
		{
			const polyPatch& patch = mesh.boundaryMesh()[patchI];

			const Field<Type>& patchField = initialPatchValuePtrs_[patchI];

			forAll(patch.faceCentres(), patchFaceI)
			{
				label meshFaceI = patch.start() + patchFaceI;

				changedFaces[nChangedFaces] = meshFaceI;

				faceDist[nChangedFaces] =
					TransferType
					(
						patch.faceCentres()[patchFaceI],
						patchField[patchFaceI],
						0.0
					);

				nChangedFaces++;
			}
		}
	}
}


// Copy from MeshWave data into *this (distance) and field_ (transported data)
template<class TransferType>
tnbLib::label tnbLib::patchDataWave<TransferType>::getValues
(
	const MeshWave<TransferType>& waveInfo
)
{
	const polyMesh& mesh = cellDistFuncs::mesh();

	const List<TransferType>& cellInfo = waveInfo.allCellInfo();
	const List<TransferType>& faceInfo = waveInfo.allFaceInfo();

	label nIllegal = 0;

	// Copy cell values
	distance_.setSize(cellInfo.size());

	forAll(cellInfo, cellI)
	{
		const TransferType & wpn = cellInfo[cellI];

		scalar dist = wpn.distSqr();

		if (cellInfo[cellI].valid())
		{
			distance_[cellI] = tnbLib::sqrt(dist);

			cellData_[cellI] = cellInfo[cellI].data();
		}
		else
		{
			// Illegal/unset value. What to do with data?

			distance_[cellI] = dist;

			//cellData_[cellI] = wallPoint::greatPoint;
			cellData_[cellI] = cellInfo[cellI].data();

			nIllegal++;
		}
	}

	// Copy boundary values
	forAll(patchDistance_, patchI)
	{
		const polyPatch& patch = mesh.boundaryMesh()[patchI];

		// Allocate storage for patchDistance
		scalarField* patchFieldPtr = new scalarField(patch.size());

		patchDistance_.set(patchI, patchFieldPtr);

		scalarField& patchField = *patchFieldPtr;

		// Allocate storage for patchData
		Field<Type>* patchDataFieldPtr = new Field<Type>(patch.size());

		patchData_.set(patchI, patchDataFieldPtr);

		Field<Type>& patchDataField = *patchDataFieldPtr;

		// Copy distance and data
		forAll(patchField, patchFaceI)
		{
			label meshFaceI = patch.start() + patchFaceI;

			scalar dist = faceInfo[meshFaceI].distSqr();

			if (faceInfo[meshFaceI].valid())
			{
				// Adding SMALL to avoid problems with /0 in the turbulence
				// models
				patchField[patchFaceI] = tnbLib::sqrt(dist) + SMALL;

				patchDataField[patchFaceI] = faceInfo[meshFaceI].data();
			}
			else
			{
				// Illegal/unset value. What to do with data?

				patchField[patchFaceI] = dist;

				//patchDataField[patchFaceI] = wallPoint::greatPoint;
				patchDataField[patchFaceI] = faceInfo[meshFaceI].data();

				nIllegal++;
			}
		}
	}

	return nIllegal;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
template<class TransferType>
tnbLib::patchDataWave<TransferType>::patchDataWave
(
	const polyMesh& mesh,
	const labelHashSet& patchIDs,
	const UPtrList<Field<Type> >& initialPatchValuePtrs,
	const bool correctWalls
)
	:
	cellDistFuncs(mesh),
	patchIDs_(patchIDs),
	initialPatchValuePtrs_(initialPatchValuePtrs),
	correctWalls_(correctWalls),
	nUnset_(0),
	distance_(mesh.nCells()),
	patchDistance_(mesh.boundaryMesh().size()),
	cellData_(mesh.nCells()),
	patchData_(mesh.boundaryMesh().size())
{
	patchDataWave<TransferType>::correct();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class TransferType>
tnbLib::patchDataWave<TransferType>::~patchDataWave()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Correct for mesh geom/topo changes
template<class TransferType>
void tnbLib::patchDataWave<TransferType>::correct()
{
	//
	// Set initial changed faces: set TransferType for wall faces
	// to wall centre.
	//

	// Count walls
	label nWalls = sumPatchSize(patchIDs_);

	List<TransferType> faceDist(nWalls);
	labelList changedFaces(nWalls);

	setChangedFaces(patchIDs_, changedFaces, faceDist);

	//
	// Do calculate wall distance by 'growing' from faces.
	//

	MeshWave<TransferType> waveInfo
	(
		mesh(),
		changedFaces,
		faceDist,
		mesh().globalData().nTotalCells() // max iterations
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

		// Get distance and indices of nearest face
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

		// Transfer data from nearest face to cell
		const List<TransferType>& faceInfo = waveInfo.allFaceInfo();

		const labelList wallCells(nearestFace.toc());

		forAll(wallCells, wallCellI)
		{
			label cellI = wallCells[wallCellI];

			label faceI = nearestFace[cellI];

			cellData_[cellI] = faceInfo[faceI].data();
		}
	}
}


// ************************************************************************* //