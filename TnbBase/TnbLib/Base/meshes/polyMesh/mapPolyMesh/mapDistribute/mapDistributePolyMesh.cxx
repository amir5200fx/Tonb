#include <mapDistributePolyMesh.hxx>

#include <polyMesh.hxx>
#include <PstreamReduceOps.hxx>
#include <ListOps.hxx>
#include <polyBoundaryMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::mapDistributePolyMesh::calcPatchSizes()
{
	oldPatchSizes_.setSize(oldPatchStarts_.size());

	// Calculate old patch sizes
	for (label patchI = 0; patchI < oldPatchStarts_.size() - 1; patchI++)
	{
		oldPatchSizes_[patchI] =
			oldPatchStarts_[patchI + 1] - oldPatchStarts_[patchI];
	}

	// Set the last one by hand
	const label lastPatchID = oldPatchStarts_.size() - 1;

	oldPatchSizes_[lastPatchID] = nOldFaces_ - oldPatchStarts_[lastPatchID];

	if (min(oldPatchSizes_) < 0)
	{
		FatalErrorIn("mapDistributePolyMesh::calcPatchSizes()")
			<< "Calculated negative old patch size:" << oldPatchSizes_ << nl
			<< "Error in mapping data" << abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct from components
tnbLib::mapDistributePolyMesh::mapDistributePolyMesh
(
	const polyMesh& mesh,

	// mesh before changes
	const label nOldPoints,
	const label nOldFaces,
	const label nOldCells,
	const labelList& oldPatchStarts,
	const labelList& oldPatchNMeshPoints,

	// how to subset pieces of mesh to send across
	const labelListList& subPointMap,
	const labelListList& subFaceMap,
	const labelListList& subCellMap,
	const labelListList& subPatchMap,

	// how to reconstruct received mesh
	const labelListList& constructPointMap,
	const labelListList& constructFaceMap,
	const labelListList& constructCellMap,
	const labelListList& constructPatchMap
)
	:
mesh_(mesh),
nOldPoints_(nOldPoints),
nOldFaces_(nOldFaces),
nOldCells_(nOldCells),
oldPatchSizes_(oldPatchStarts.size()),
oldPatchStarts_(oldPatchStarts),
oldPatchNMeshPoints_(oldPatchNMeshPoints),
pointMap_(mesh.nPoints(), subPointMap, constructPointMap),
faceMap_(mesh.nFaces(), subFaceMap, constructFaceMap),
cellMap_(mesh.nCells(), subCellMap, constructCellMap),
patchMap_(mesh.boundaryMesh().size(), subPatchMap, constructPatchMap)
{
	calcPatchSizes();
}


//- (optionally destructively) construct from components
tnbLib::mapDistributePolyMesh::mapDistributePolyMesh
(
	const polyMesh& mesh,
	const label nOldPoints,
	const label nOldFaces,
	const label nOldCells,
	labelList& oldPatchStarts,
	labelList& oldPatchNMeshPoints,

	labelListList& subPointMap,
	labelListList& subFaceMap,
	labelListList& subCellMap,
	labelListList& subPatchMap,
	labelListList& constructPointMap,
	labelListList& constructFaceMap,
	labelListList& constructCellMap,
	labelListList& constructPatchMap,
	const bool reUse                // clone or reuse
)
	:
	mesh_(mesh),
	nOldPoints_(nOldPoints),
	nOldFaces_(nOldFaces),
	nOldCells_(nOldCells),
	oldPatchSizes_(oldPatchStarts.size()),
	oldPatchStarts_(oldPatchStarts, reUse),
	oldPatchNMeshPoints_(oldPatchNMeshPoints, reUse),

	pointMap_(mesh.nPoints(), subPointMap, constructPointMap, reUse),
	faceMap_(mesh.nFaces(), subFaceMap, constructFaceMap, reUse),
	cellMap_(mesh.nCells(), subCellMap, constructCellMap, reUse),
	patchMap_(mesh.boundaryMesh().size(), subPatchMap, constructPatchMap, reUse)
{
	calcPatchSizes();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mapDistributePolyMesh::distributePointIndices(labelList& lst) const
{
	// Construct boolList from selected elements
	boolList isSelected
	(
		createWithValues<boolList>
		(
			nOldPoints(),
			false,
			lst,
			true
			)
	);

	// Distribute
	distributePointData(isSelected);

	// Collect selected elements
	lst = findIndices(isSelected, true);
}


void tnbLib::mapDistributePolyMesh::distributeFaceIndices(labelList& lst) const
{
	// Construct boolList from selected elements
	boolList isSelected
	(
		createWithValues<boolList>
		(
			nOldFaces(),
			false,
			lst,
			true
			)
	);

	// Distribute
	distributeFaceData(isSelected);

	// Collect selected elements
	lst = findIndices(isSelected, true);
}


void tnbLib::mapDistributePolyMesh::distributeCellIndices(labelList& lst) const
{
	// Construct boolList from selected elements
	boolList isSelected
	(
		createWithValues<boolList>
		(
			nOldCells(),
			false,
			lst,
			true
			)
	);

	// Distribute
	distributeCellData(isSelected);

	// Collect selected elements
	lst = findIndices(isSelected, true);
}


void tnbLib::mapDistributePolyMesh::distributePatchIndices(labelList& lst) const
{
	// Construct boolList from selected elements
	boolList isSelected
	(
		createWithValues<boolList>
		(
			oldPatchStarts().size(),    // nOldPatches
			false,
			lst,
			true
			)
	);

	// Distribute
	distributePatchData(isSelected);

	// Collect selected elements
	lst = findIndices(isSelected, true);
}


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// ************************************************************************* //