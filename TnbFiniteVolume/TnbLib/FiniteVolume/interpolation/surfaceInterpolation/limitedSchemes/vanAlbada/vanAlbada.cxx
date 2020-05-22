#include <vanAlbada.hxx>

#include <LimitedScheme.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(vanAlbada, vanAlbadaLimiter)
		makeLimitedVSurfaceInterpolationScheme(vanAlbadaV, vanAlbadaLimiter)
}

// ************************************************************************* //