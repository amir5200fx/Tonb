#include <QUICK.hxx>

#include <LimitedScheme.hxx>
#include <QUICKV.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makeLimitedSurfaceInterpolationScheme(QUICK, QUICKLimiter)
		makeLimitedVSurfaceInterpolationScheme(QUICKV, QUICKVLimiter)
}

// ************************************************************************* //