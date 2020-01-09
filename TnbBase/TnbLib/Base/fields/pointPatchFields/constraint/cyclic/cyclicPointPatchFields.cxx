#include <cyclicPointPatchFields.hxx>

#include <pointPatchFields.hxx>
#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makePointPatchFields(cyclic, pointPatch, PointPatch);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //