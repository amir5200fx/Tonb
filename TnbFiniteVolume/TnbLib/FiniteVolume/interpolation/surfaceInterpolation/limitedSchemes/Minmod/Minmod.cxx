#include <Minmod.hxx>

#include <LimitedScheme.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(Minmod, MinmodLimiter)
		makeLimitedVSurfaceInterpolationScheme(MinmodV, MinmodLimiter)
}

// ************************************************************************* //