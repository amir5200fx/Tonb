#include <limitedLinear.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(limitedLinear, limitedLinearLimiter)

		makeLimitedVSurfaceInterpolationScheme
		(
			limitedLinearV,
			limitedLinearLimiter
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedLimitedLinear,
			LimitedLimiter,
			limitedLinearLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedLinear01,
			Limited01Limiter,
			limitedLinearLimiter,
			NVDTVD,
			magSqr,
			scalar
		)
}

// ************************************************************************* //