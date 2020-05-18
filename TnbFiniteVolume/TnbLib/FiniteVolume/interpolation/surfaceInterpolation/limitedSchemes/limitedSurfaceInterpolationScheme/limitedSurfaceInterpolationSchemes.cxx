#include <limitedSurfaceInterpolationScheme.hxx>

#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeBaseLimitedSurfaceInterpolationScheme(Type)                       \
                                                                              \
defineNamedTemplateTypeNameAndDebug(limitedSurfaceInterpolationScheme<Type>, 0);\
                                                                              \
defineTemplateRunTimeSelectionTable                                           \
(                                                                             \
    limitedSurfaceInterpolationScheme<Type>,                                  \
    Mesh                                                                      \
);                                                                            \
                                                                              \
defineTemplateRunTimeSelectionTable                                           \
(                                                                             \
    limitedSurfaceInterpolationScheme<Type>,                                  \
    MeshFlux                                                                  \
);

	makeBaseLimitedSurfaceInterpolationScheme(scalar)
		makeBaseLimitedSurfaceInterpolationScheme(vector)
		makeBaseLimitedSurfaceInterpolationScheme(sphericalTensor)
		makeBaseLimitedSurfaceInterpolationScheme(symmTensor)
		makeBaseLimitedSurfaceInterpolationScheme(symmTensor4thOrder)
		makeBaseLimitedSurfaceInterpolationScheme(diagTensor)
		makeBaseLimitedSurfaceInterpolationScheme(tensor)


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //