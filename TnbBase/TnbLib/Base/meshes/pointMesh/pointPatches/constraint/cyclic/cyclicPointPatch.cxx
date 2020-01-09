#include <cyclicPointPatch.hxx>

#include <cyclicPointPatchFields.hxx>

#include <pointBoundaryMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <pointMesh.hxx>
#include <globalPointPatch.hxx>
#include <edgeList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(cyclicPointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		cyclicPointPatch,
		polyPatch
	);


	void cyclicPointPatch::initUpdateMesh()
	{
		facePointPatch::initUpdateMesh();
	}


	void cyclicPointPatch::updateMesh()
	{
		facePointPatch::updateMesh();
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	cyclicPointPatch::cyclicPointPatch
	(
		const polyPatch& patch,
		const pointBoundaryMesh& bm
	)
		:
		coupledFacePointPatch(patch, bm),
		cyclicPolyPatch_(refCast<const cyclicPolyPatch>(patch))
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	cyclicPointPatch::~cyclicPointPatch()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //



	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //