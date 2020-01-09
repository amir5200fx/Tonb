#include <wedgePointPatch.hxx>

#include <pointConstraint.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(wedgePointPatch, 0);

	// Add the patch constructor functions to the hash tables
	addToRunTimeSelectionTable
	(
		facePointPatch,
		wedgePointPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void wedgePointPatch::applyConstraint
	(
		const label pointi,
		pointConstraint& pc
	) const
	{
		pc.applyConstraint(pointNormals()[pointi]);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //