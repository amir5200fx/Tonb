#include <fvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeFvPatchField(fvPatchTypeField)                                    \
                                                                              \
defineNamedTemplateTypeNameAndDebug(fvPatchTypeField, 0);                     \
template<>                                                                    \
tnbLib::debug::debugSwitch                                                      \
fvPatchTypeField::disallowGenericFvPatchField                                 \
(                                                                             \
    "disallowGenericFvPatchField",                                            \
    0                                                                         \
);                                                                            \
defineTemplateRunTimeSelectionTable(fvPatchTypeField, patch);                 \
defineTemplateRunTimeSelectionTable(fvPatchTypeField, patchMapper);           \
defineTemplateRunTimeSelectionTable(fvPatchTypeField, dictionary);

	makeFvPatchField(fvPatchScalarField)
		makeFvPatchField(fvPatchVectorField)
		makeFvPatchField(fvPatchSphericalTensorField)
		makeFvPatchField(fvPatchSymmTensorField)
		makeFvPatchField(fvPatchSymmTensor4thOrderField)
		makeFvPatchField(fvPatchDiagTensorField)
		makeFvPatchField(fvPatchTensorField)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //