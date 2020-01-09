#include <cyclicGgiPointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicGgiPointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		cyclicGgiPointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::cyclicGgiPointPatch::initUpdateMesh()
{
	facePointPatch::initUpdateMesh();
}


void tnbLib::cyclicGgiPointPatch::updateMesh()
{
	facePointPatch::updateMesh();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct from components
tnbLib::cyclicGgiPointPatch::cyclicGgiPointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	coupledFacePointPatch(patch, bm),
	cyclicGgiPolyPatch_(refCast<const cyclicGgiPolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicGgiPointPatch::~cyclicGgiPointPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::cyclicGgiPointPatch::coupled() const
{
	return true;
}


// ************************************************************************* //