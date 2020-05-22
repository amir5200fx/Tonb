#include <SFCD.hxx>

#include <LimitedScheme.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(SFCD, SFCDLimiter)
		makeLimitedVSurfaceInterpolationScheme(SFCDV, SFCDLimiter)
}

// ************************************************************************* //