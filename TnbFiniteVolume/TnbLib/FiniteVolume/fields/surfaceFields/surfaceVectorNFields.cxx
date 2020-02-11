#include <surfaceVectorNFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define doMakeSurfaceFields(type, Type, args)                \
    defineTemplateTypeNameAndDebug(                             \
        surface##Type##Field::DimensionedInternalField, 0);     \
                                                                \
    defineTemplateTypeNameAndDebug(surface##Type##Field, 0);

	forAllVectorNTypes(doMakeSurfaceFields)

		forAllTensorNTypes(doMakeSurfaceFields)

		forAllDiagTensorNTypes(doMakeSurfaceFields)

		forAllSphericalTensorNTypes(doMakeSurfaceFields)

#undef doMakeSurfaceFields

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //