#include <fixedNormalSlipFvPatchFields.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makeTemplatePatchTypeField
	(
		fvPatchVectorField,
		fixedNormalSlipFvPatchVectorField
	);

	makeTemplatePatchTypeField
	(
		fvPatchTensorField,
		fixedNormalSlipFvPatchTensorField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //