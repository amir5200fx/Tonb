#include <oscillatingFixedValuePointPatchFields.hxx>

#include <pointBoundaryMesh.hxx>
#include <pointPatchFields.hxx>
#include <pointMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makePointPatchFields(oscillatingFixedValue, pointPatch, PointPatch);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //