#include <mixingPlanePointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mixingPlanePointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		mixingPlanePointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::mixingPlanePointPatch::initUpdateMesh()
{
	facePointPatch::initUpdateMesh();
}


void tnbLib::mixingPlanePointPatch::updateMesh()
{
	facePointPatch::updateMesh();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct from components
tnbLib::mixingPlanePointPatch::mixingPlanePointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	coupledFacePointPatch(patch, bm),
	mixingPlanePolyPatch_(refCast<const mixingPlanePolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::mixingPlanePointPatch::~mixingPlanePointPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::mixingPlanePointPatch::coupled() const
{
	return true;
}


// ************************************************************************* //