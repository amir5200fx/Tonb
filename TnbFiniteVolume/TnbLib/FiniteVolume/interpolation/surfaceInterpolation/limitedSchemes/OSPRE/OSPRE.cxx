#include <OSPRE.hxx>

#include <LimitedScheme.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(OSPRE, OSPRELimiter)
		makeLimitedVSurfaceInterpolationScheme(OSPREV, OSPRELimiter)
}

// ************************************************************************* //