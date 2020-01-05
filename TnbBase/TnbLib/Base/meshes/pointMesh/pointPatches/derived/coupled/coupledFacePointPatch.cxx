#include <coupledFacePointPatch.hxx>

#include <pointBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(coupledFacePointPatch, 0);


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	coupledFacePointPatch::coupledFacePointPatch
	(
		const polyPatch& patch,
		const pointBoundaryMesh& bm
	)
		:
		facePointPatch(patch, bm),
		coupledPointPatch(bm),
		coupledPolyPatch_(refCast<const coupledPolyPatch>(patch))
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	coupledFacePointPatch::~coupledFacePointPatch()
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //