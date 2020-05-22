#include <UMIST.hxx>

#include <LimitedScheme.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(UMIST, UMISTLimiter)
		makeLimitedVSurfaceInterpolationScheme(UMISTV, UMISTLimiter)
}

// ************************************************************************* //