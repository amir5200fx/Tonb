#include <MeshWave.hxx>

#include <polyMesh.hxx>
#include <processorPolyPatch.hxx>
#include <cyclicPolyPatch.hxx>
#include <OPstream.hxx>
#include <IPstream.hxx>
#include <PstreamReduceOps.hxx>
#include <tnbDebug.hxx>
#include <typeInfo.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Iterate, propagating changedFacesInfo across mesh, until no change (or
// maxIter reached).
template <class Type>
tnbLib::MeshWave<Type>::MeshWave
(
	const polyMesh& mesh,
	const labelList& changedFaces,
	const List<Type>& changedFacesInfo,
	const label maxIter
)
	:
	allFaceInfo_(mesh.nFaces()),
	allCellInfo_(mesh.nCells()),
	calc_
	(
		mesh,
		changedFaces,
		changedFacesInfo,
		allFaceInfo_,
		allCellInfo_,
		maxIter
	)
{}


// Iterate, propagating changedFacesInfo across mesh, until no change (or
// maxIter reached). Initial cell values specified.
template <class Type>
tnbLib::MeshWave<Type>::MeshWave
(
	const polyMesh& mesh,
	const labelList& changedFaces,
	const List<Type>& changedFacesInfo,
	const List<Type>& allCellInfo,
	const label maxIter
)
	:
	allFaceInfo_(mesh.nFaces()),
	allCellInfo_(allCellInfo),
	calc_
	(
		mesh,
		changedFaces,
		changedFacesInfo,
		allFaceInfo_,
		allCellInfo_,
		maxIter
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// ************************************************************************* //