#include <timeVaryingUniformFixedValuePointPatchFields.hxx>

#include <pointPatchFields.hxx>
#include <pointBoundaryMesh.hxx>
#include <pointMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makePointPatchFields(timeVaryingUniformFixedValue, pointPatch, PointPatch);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //