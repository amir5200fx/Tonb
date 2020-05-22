#include <filteredLinear.hxx>

#include <LimitedScheme.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme
	(
		filteredLinear,
		filteredLinearLimiter
	)
}

// ************************************************************************* //