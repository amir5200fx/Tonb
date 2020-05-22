#include <fvPatchVectorNFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeFvPatchField(fvPatchTypeField)                                    \
                                                                              \
defineNamedTemplateTypeNameAndDebug(fvPatchTypeField, 0);                     \
template<>                                                                    \
debug::debugSwitch                                                            \
fvPatchTypeField::disallowGenericFvPatchField                                 \
(                                                                             \
    "disallowGenericFvPatchField",                                            \
    0                                                                         \
);                                                                            \
defineTemplateRunTimeSelectionTable(fvPatchTypeField, patch);                 \
defineTemplateRunTimeSelectionTable(fvPatchTypeField, patchMapper);           \
defineTemplateRunTimeSelectionTable(fvPatchTypeField, dictionary);


#define doMakeFvPatchField(type, Type, args)                               \
    makeFvPatchField(fvPatch##Type##Field)

	forAllVectorNTypes(doMakeFvPatchField)

		forAllTensorNTypes(doMakeFvPatchField)

		forAllDiagTensorNTypes(doMakeFvPatchField)

		forAllSphericalTensorNTypes(doMakeFvPatchField)

#undef doMakeFvPatchField
#undef makeFvPatchField

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //