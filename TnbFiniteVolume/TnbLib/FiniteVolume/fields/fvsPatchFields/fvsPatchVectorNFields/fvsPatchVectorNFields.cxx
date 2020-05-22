#include <fvsPatchVectorNFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeFvsPatchField(fvsPatchTypeField)                                  \
                                                                              \
defineNamedTemplateTypeNameAndDebug(fvsPatchTypeField, 0);                    \
template<>                                                                    \
tnbLib::debug::debugSwitch                                                      \
fvsPatchTypeField::disallowDefaultFvsPatchField                               \
(                                                                             \
    "disallowDefaultFvsPatchField",                                           \
    0                                                                         \
);                                                                            \
defineTemplateRunTimeSelectionTable(fvsPatchTypeField, patch);                \
defineTemplateRunTimeSelectionTable(fvsPatchTypeField, patchMapper);          \
defineTemplateRunTimeSelectionTable(fvsPatchTypeField, dictionary);

#define doMakeFvsPatchField(type, Type, args)    \
    makeFvsPatchField(fvsPatch##Type##Field)

	forAllVectorNTypes(doMakeFvsPatchField)

		forAllTensorNTypes(doMakeFvsPatchField)

		forAllDiagTensorNTypes(doMakeFvsPatchField)

		forAllSphericalTensorNTypes(doMakeFvsPatchField)

#undef makeFvsPatchField
#undef doMakeFvsPatchField

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //