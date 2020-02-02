#include <transformFvPatchVectorNFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

#define makePatch(type, Type, args)                                        \
    defineNamedTemplateTypeNameAndDebug(transformFvPatch##Type##Field, 0);

	forAllVectorNTypes(makePatch)

		forAllTensorNTypes(makePatch)

		forAllDiagTensorNTypes(makePatch)

		forAllSphericalTensorNTypes(makePatch)

#undef makePatch

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //