#include <Gamma.hxx>

#include <LimitedScheme.hxx>
#include <Limited01.hxx>
#include <DeferredCorrectionLimitedScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(Gamma, GammaLimiter)
		makeLimitedVSurfaceInterpolationScheme(GammaV, GammaLimiter)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			limitedGamma,
			LimitedLimiter,
			GammaLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		makeLLimitedSurfaceInterpolationTypeScheme
		(
			Gamma01,
			Limited01Limiter,
			GammaLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

		// Deferred correction schemes
		makeDeferredSurfaceInterpolationScheme(GammaDC, GammaLimiter)
		makeDeferredVSurfaceInterpolationScheme(GammaVDC, GammaLimiter)

		makeLDeferredSurfaceInterpolationTypeScheme
		(
			Gamma01DC,
			Limited01Limiter,
			GammaLimiter,
			NVDTVD,
			magSqr,
			scalar
		)

}

// ************************************************************************* //