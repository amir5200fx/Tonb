#include <regionCouplePointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(regionCouplePointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		regionCouplePointPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

	void tnbLib::regionCouplePointPatch::initUpdateMesh()
	{
		facePointPatch::initUpdateMesh();
	}


	void tnbLib::regionCouplePointPatch::updateMesh()
	{
		facePointPatch::updateMesh();
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	//- Construct from components
	regionCouplePointPatch::regionCouplePointPatch
	(
		const polyPatch& patch,
		const pointBoundaryMesh& bm
	)
		:
		coupledFacePointPatch(patch, bm),
		regionCouplePolyPatch_(refCast<const regionCouplePolyPatch>(patch))
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	regionCouplePointPatch::~regionCouplePointPatch()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	bool regionCouplePointPatch::coupled() const
	{
		// Consider options: coupled or uncoupled for post-processing?
		// HJ, 26/Feb/2008
	//     return false;

		return patch().coupled();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //