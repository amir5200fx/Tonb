#include <mapPolyMesh.hxx>

#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from mesh.  No morphing data: the mesh has not changed
// HJ, 27/Nov/2009
tnbLib::mapPolyMesh::mapPolyMesh(const polyMesh& mesh)
	:
	mesh_(mesh),
	morphing_(false),
	nOldPoints_(mesh.nPoints()),
	nOldFaces_(mesh.nFaces()),
	nOldCells_(mesh.nCells())
{}


// Construct from components
tnbLib::mapPolyMesh::mapPolyMesh
(
	const polyMesh& mesh,
	const label nOldPoints,
	const label nOldFaces,
	const label nOldCells,
	const labelList& pointMap,
	const List<objectMap>& pointsFromPoints,
	const labelList& faceMap,
	const List<objectMap>& facesFromPoints,
	const List<objectMap>& facesFromEdges,
	const List<objectMap>& facesFromFaces,
	const labelList& cellMap,
	const List<objectMap>& cellsFromPoints,
	const List<objectMap>& cellsFromEdges,
	const List<objectMap>& cellsFromFaces,
	const List<objectMap>& cellsFromCells,
	const labelList& reversePointMap,
	const labelList& reverseFaceMap,
	const labelList& reverseCellMap,
	const labelHashSet& flipFaceFlux,
	const labelListList& patchPointMap,
	const labelListList& pointZoneMap,
	const labelListList& faceZonePointMap,
	const labelListList& faceZoneFaceMap,
	const labelListList& cellZoneMap,
	const pointField& preMotionPoints,
	const labelList& oldPatchStarts,
	const labelList& oldPatchNMeshPoints
)
	:
mesh_(mesh),
morphing_(true),  // The mesh is morphing
nOldPoints_(nOldPoints),
nOldFaces_(nOldFaces),
nOldCells_(nOldCells),
pointMap_(pointMap),
pointsFromPointsMap_(pointsFromPoints),
faceMap_(faceMap),
facesFromPointsMap_(facesFromPoints),
facesFromEdgesMap_(facesFromEdges),
facesFromFacesMap_(facesFromFaces),
cellMap_(cellMap),
cellsFromPointsMap_(cellsFromPoints),
cellsFromEdgesMap_(cellsFromEdges),
cellsFromFacesMap_(cellsFromFaces),
cellsFromCellsMap_(cellsFromCells),
reversePointMap_(reversePointMap),
reverseFaceMap_(reverseFaceMap),
reverseCellMap_(reverseCellMap),
flipFaceFlux_(flipFaceFlux),
patchPointMap_(patchPointMap),
pointZoneMap_(pointZoneMap),
faceZonePointMap_(faceZonePointMap),
faceZoneFaceMap_(faceZoneFaceMap),
cellZoneMap_(cellZoneMap),
preMotionPoints_(preMotionPoints),
oldPatchSizes_(oldPatchStarts.size()),
oldPatchStarts_(oldPatchStarts),
oldPatchNMeshPoints_(oldPatchNMeshPoints)
{
	// Calculate old patch sizes
	for (label patchI = 0; patchI < oldPatchStarts_.size() - 1; patchI++)
	{
		oldPatchSizes_[patchI] =
			oldPatchStarts_[patchI + 1] - oldPatchStarts_[patchI];
	}

	// Set the last one by hand
	const label lastPatchID = oldPatchStarts_.size() - 1;

	oldPatchSizes_[lastPatchID] = nOldFaces_ - oldPatchStarts_[lastPatchID];

	if (polyMesh::debug)
	{
		if (min(oldPatchSizes_) < 0)
		{
			FatalErrorIn("mapPolyMesh::mapPolyMesh(...)")
				<< "Calculated negative old patch size.  Error in mapping data"
				<< abort(FatalError);
		}
	}
}


// Construct from components and optionally reuse storage
tnbLib::mapPolyMesh::mapPolyMesh
(
	const polyMesh& mesh,
	const label nOldPoints,
	const label nOldFaces,
	const label nOldCells,
	labelList& pointMap,
	List<objectMap>& pointsFromPoints,
	labelList& faceMap,
	List<objectMap>& facesFromPoints,
	List<objectMap>& facesFromEdges,
	List<objectMap>& facesFromFaces,
	labelList& cellMap,
	List<objectMap>& cellsFromPoints,
	List<objectMap>& cellsFromEdges,
	List<objectMap>& cellsFromFaces,
	List<objectMap>& cellsFromCells,
	labelList& reversePointMap,
	labelList& reverseFaceMap,
	labelList& reverseCellMap,
	labelHashSet& flipFaceFlux,
	labelListList& patchPointMap,
	labelListList& pointZoneMap,
	labelListList& faceZonePointMap,
	labelListList& faceZoneFaceMap,
	labelListList& cellZoneMap,
	pointField& preMotionPoints,
	labelList& oldPatchStarts,
	labelList& oldPatchNMeshPoints,
	const bool reUse
)
	:
mesh_(mesh),
morphing_(true),  // The mesh is morphing
nOldPoints_(nOldPoints),
nOldFaces_(nOldFaces),
nOldCells_(nOldCells),
pointMap_(pointMap, reUse),
pointsFromPointsMap_(pointsFromPoints, reUse),
faceMap_(faceMap, reUse),
facesFromPointsMap_(facesFromPoints, reUse),
facesFromEdgesMap_(facesFromEdges, reUse),
facesFromFacesMap_(facesFromFaces, reUse),
cellMap_(cellMap, reUse),
cellsFromPointsMap_(cellsFromPoints, reUse),
cellsFromEdgesMap_(cellsFromEdges, reUse),
cellsFromFacesMap_(cellsFromFaces, reUse),
cellsFromCellsMap_(cellsFromCells, reUse),
reversePointMap_(reversePointMap, reUse),
reverseFaceMap_(reverseFaceMap, reUse),
reverseCellMap_(reverseCellMap, reUse),
flipFaceFlux_(flipFaceFlux),
patchPointMap_(patchPointMap, reUse),
pointZoneMap_(pointZoneMap, reUse),
faceZonePointMap_(faceZonePointMap, reUse),
faceZoneFaceMap_(faceZoneFaceMap, reUse),
cellZoneMap_(cellZoneMap, reUse),
preMotionPoints_(preMotionPoints, reUse),
oldPatchSizes_(oldPatchStarts.size()),
oldPatchStarts_(oldPatchStarts, reUse),
oldPatchNMeshPoints_(oldPatchNMeshPoints, reUse)
{
	// Calculate old patch sizes
	for (label patchI = 0; patchI < oldPatchStarts_.size() - 1; patchI++)
	{
		oldPatchSizes_[patchI] =
			oldPatchStarts_[patchI + 1] - oldPatchStarts_[patchI];
	}

	// Set the last one by hand
	const label lastPatchID = oldPatchStarts_.size() - 1;

	oldPatchSizes_[lastPatchID] = nOldFaces_ - oldPatchStarts_[lastPatchID];

	if (polyMesh::debug)
	{
		if (min(oldPatchSizes_) < 0)
		{
			FatalErrorIn("mapPolyMesh::mapPolyMesh(...)")
				<< "Calculated negative old patch size.  Error in mapping data"
				<< abort(FatalError);
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// ************************************************************************* //