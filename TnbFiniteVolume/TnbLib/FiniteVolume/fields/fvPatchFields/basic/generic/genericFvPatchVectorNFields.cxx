#include <genericFvPatchVectorNFields.hxx>

#include <fvPatchVectorNFields.hxx>
#include <volVectorNFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define doMakePatchTypeField(type, Type, args)           \
    makePatchTypeFieldTypeName(genericFvPatch##Type##Field);

	forAllVectorNTypes(doMakePatchTypeField)

		forAllTensorNTypes(doMakePatchTypeField)

		forAllDiagTensorNTypes(doMakePatchTypeField)

		forAllSphericalTensorNTypes(doMakePatchTypeField)

#undef doMakePatchTypeField

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
