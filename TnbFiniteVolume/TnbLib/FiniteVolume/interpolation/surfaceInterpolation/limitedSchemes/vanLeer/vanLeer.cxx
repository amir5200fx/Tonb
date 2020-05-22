#include <vanLeer.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <DeferredCorrectionLimitedScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(vanLeer, vanLeerLimiter)
		makeLimitedVSurfaceInterpolationScheme(vanLeerV, vanLeerLimiter)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedVanLeer,
			LimitedLimiter,
			vanLeerLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			vanLeer01,
			Limited01Limiter,
			vanLeerLimiter,
			NVDTVD,
			magSqr,
			scalar
		)


		// Deferred correction schemes
		makeDeferredSurfaceInterpolationScheme(vanLeerDC, vanLeerLimiter)
		makeDeferredVSurfaceInterpolationScheme(vanLeerVDC, vanLeerLimiter)

		makeLDeferredSurfaceInterpolationTypeScheme
		(
			vanLeer01DC,
			Limited01Limiter,
			vanLeerLimiter,
			NVDTVD,
			magSqr,
			scalar
		)
}

// ************************************************************************* //