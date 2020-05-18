#include <limitedSurfaceInterpolationScheme.hxx>

#include <fvMesh.hxx>

template<class Type>
inline tnbLib::limitedSurfaceInterpolationScheme<Type>::limitedSurfaceInterpolationScheme
(
	const fvMesh & mesh, 
	Istream & is
)
	: surfaceInterpolationScheme<Type>(mesh)
	, faceFlux_
	(
		mesh.lookupObject<surfaceScalarField>
		(
			word(is)
			)
	)
{
}
