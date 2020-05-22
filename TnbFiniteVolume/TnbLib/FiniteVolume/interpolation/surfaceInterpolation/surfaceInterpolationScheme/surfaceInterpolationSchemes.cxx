#include <surfaceInterpolationScheme.hxx>

#include <GeometricFields.hxx>
#include <volMesh.hxx>
#include <surfaceMesh.hxx>

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

	makeBaseSurfaceInterpolationScheme(scalar)
		makeBaseSurfaceInterpolationScheme(vector)
		makeBaseSurfaceInterpolationScheme(sphericalTensor)
		makeBaseSurfaceInterpolationScheme(symmTensor)
		makeBaseSurfaceInterpolationScheme(symmTensor4thOrder)
		makeBaseSurfaceInterpolationScheme(diagTensor)
		makeBaseSurfaceInterpolationScheme(tensor)


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //