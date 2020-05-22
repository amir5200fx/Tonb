#include <surfaceInterpolationScheme.hxx>

#include <VectorNFieldTypes.hxx>
#include <linear.hxx>
#include <reverseLinear.hxx>
#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeBaseSurfaceInterpolationScheme(Type)                              \
                                                                              \
defineNamedTemplateTypeNameAndDebug(surfaceInterpolationScheme<Type>, 0);     \
                                                                              \
defineTemplateRunTimeSelectionTable                                           \
(                                                                             \
    surfaceInterpolationScheme<Type>,                                         \
    Mesh                                                                      \
);                                                                            \
                                                                              \
defineTemplateRunTimeSelectionTable                                           \
(                                                                             \
    surfaceInterpolationScheme<Type>,                                         \
    MeshFlux                                                                  \
);


#define doMakeSchemes(type, Type, args)                                    \
    makeBaseSurfaceInterpolationScheme(type)                                  \
                                                                              \
    makeSurfaceInterpolationTypeScheme(linear, type)                          \
    makeSurfaceInterpolationTypeScheme(reverseLinear, type)

	forAllVectorNTypes(doMakeSchemes)

		forAllTensorNTypes(doMakeSchemes)

		forAllDiagTensorNTypes(doMakeSchemes)

		forAllSphericalTensorNTypes(doMakeSchemes)

#undef doMakeSchemes

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //