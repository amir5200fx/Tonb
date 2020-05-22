#include <filteredLinear2.hxx>

#include <LimitedScheme.hxx>
#include <filteredLinear2V.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme
	(
		filteredLinear2,
		filteredLinear2Limiter
	)

		makeLimitedVSurfaceInterpolationScheme
		(
			filteredLinear2V,
			filteredLinear2VLimiter
		)
}

// ************************************************************************* //