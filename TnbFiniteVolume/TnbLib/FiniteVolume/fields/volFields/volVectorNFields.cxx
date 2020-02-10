#include <volVectorNFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define doMakeVolFields(type, Type, args)                    \
    defineTemplateTypeNameAndDebug(                             \
        vol##Type##Field::DimensionedInternalField, 0);         \
                                                                \
    defineTemplateTypeNameAndDebug(vol##Type##Field, 0);

	forAllVectorNTypes(doMakeVolFields)

		forAllTensorNTypes(doMakeVolFields)

		forAllDiagTensorNTypes(doMakeVolFields)

		forAllSphericalTensorNTypes(doMakeVolFields)

#undef doMakeVolFields

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //