#include <overlapGgiPointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(overlapGgiPointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		overlapGgiPointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::overlapGgiPointPatch::initUpdateMesh()
{
	facePointPatch::initUpdateMesh();
}


void tnbLib::overlapGgiPointPatch::updateMesh()
{
	facePointPatch::updateMesh();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct from components
tnbLib::overlapGgiPointPatch::overlapGgiPointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	coupledFacePointPatch(patch, bm),
	overlapGgiPolyPatch_(refCast<const overlapGgiPolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::overlapGgiPointPatch::~overlapGgiPointPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::overlapGgiPointPatch::coupled() const
{
	return true;
}


// ************************************************************************* //