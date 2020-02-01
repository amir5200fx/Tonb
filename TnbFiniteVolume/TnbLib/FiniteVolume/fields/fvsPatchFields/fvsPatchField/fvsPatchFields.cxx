#include <fvsPatchFields.hxx>

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

	makeFvsPatchField(fvsPatchScalarField)
		makeFvsPatchField(fvsPatchVectorField)
		makeFvsPatchField(fvsPatchSphericalTensorField)
		makeFvsPatchField(fvsPatchSymmTensorField)
		makeFvsPatchField(fvsPatchSymmTensor4thOrderField)
		makeFvsPatchField(fvsPatchDiagTensorField)
		makeFvsPatchField(fvsPatchTensorField)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
