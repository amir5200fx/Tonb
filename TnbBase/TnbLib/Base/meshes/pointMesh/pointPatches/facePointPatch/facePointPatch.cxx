#include <facePointPatch.hxx>

#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <demandDrivenData.hxx>
#include <boolList.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(facePointPatch, 0);
	defineRunTimeSelectionTable(facePointPatch, polyPatch);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		facePointPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

	void facePointPatch::initGeometry()
	{}


	void facePointPatch::calcGeometry()
	{}


	void facePointPatch::initMovePoints(const pointField&)
	{}


	void facePointPatch::movePoints(const pointField&)
	{}


	void facePointPatch::initUpdateMesh()
	{
		facePointPatch::initGeometry();
	}


	void facePointPatch::updateMesh()
	{}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	facePointPatch::facePointPatch
	(
		const polyPatch& p,
		const pointBoundaryMesh& bm
	)
		:
		pointPatch(bm),
		polyPatch_(p)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //