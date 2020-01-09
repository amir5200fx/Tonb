#include <wallPointPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(wallPointPatch, 0);

	// Add the patch constructor functions to the hash tables
	addToRunTimeSelectionTable
	(
		facePointPatch,
		wallPointPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //