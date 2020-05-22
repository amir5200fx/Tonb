#include <SuperBee.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <DeferredCorrectionLimitedScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(SuperBee, SuperBeeLimiter)
		makeLimitedVSurfaceInterpolationScheme(SuperBeeV, SuperBeeLimiter)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			SuperBee01,
			Limited01Limiter,
			SuperBeeLimiter,
			NVDTVD,
			magSqr,
			scalar
		)


		// Deferred correction schemes
		makeDeferredSurfaceInterpolationScheme(SuperBeeDC, SuperBeeLimiter)
		makeDeferredVSurfaceInterpolationScheme(SuperBeeVDC, SuperBeeLimiter)

		makeLDeferredSurfaceInterpolationTypeScheme
		(
			SuperBee01DC,
			Limited01Limiter,
			SuperBeeLimiter,
			NVDTVD,
			magSqr,
			scalar
		)
}

// ************************************************************************* //