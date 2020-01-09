#include <ggiPointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(ggiPointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		ggiPointPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::ggiPointPatch::initUpdateMesh()
{
	facePointPatch::initUpdateMesh();
}


void tnbLib::ggiPointPatch::updateMesh()
{
	facePointPatch::updateMesh();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct from components
tnbLib::ggiPointPatch::ggiPointPatch
(
	const polyPatch& patch,
	const pointBoundaryMesh& bm
)
	:
	coupledFacePointPatch(patch, bm),
	ggiPolyPatch_(refCast<const ggiPolyPatch>(patch))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::ggiPointPatch::~ggiPointPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::ggiPointPatch::coupled() const
{
	return true;
}


// ************************************************************************* //