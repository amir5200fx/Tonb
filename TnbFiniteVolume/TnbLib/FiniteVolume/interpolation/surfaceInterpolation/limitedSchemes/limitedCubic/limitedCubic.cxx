#include <limitedCubic.hxx>

#include <Limited01.hxx>
#include <LimitedScheme.hxx>
#include <limitedCubicV.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(limitedCubic, limitedCubicLimiter)
		makeLimitedVSurfaceInterpolationScheme(limitedCubicV, limitedCubicVLimiter)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedLimitedCubic,
			LimitedLimiter,
			limitedCubicLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedCubic01,
			Limited01Limiter,
			limitedCubicLimiter,
			NVDTVD,
			magSqr,
			scalar
		)
}

// ************************************************************************* //