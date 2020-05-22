#include <multivariateScheme.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <upwind.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type, class Scheme>
	multivariateScheme<Type, Scheme>::multivariateScheme
	(
		const fvMesh& mesh,
		const typename multivariateSurfaceInterpolationScheme<Type>::
		fieldTable& fields,
		const surfaceScalarField& faceFlux,
		Istream& schemeData
	)
		:
		multivariateSurfaceInterpolationScheme<Type>
		(
			mesh,
			fields,
			faceFlux,
			schemeData
			),
		Scheme::LimiterType(schemeData),
		faceFlux_(faceFlux),
		weights_
		(
			IOobject
			(
				"multivariateWeights",
				mesh.time().timeName(),
				mesh
			),
			mesh,
			dimless
		)
	{
		typename multivariateSurfaceInterpolationScheme<Type>::
			fieldTable::const_iterator iter = this->fields().begin();

		surfaceScalarField limiter =
			Scheme(mesh, faceFlux_, *this).limiter(*iter());

		for (++iter; iter != this->fields().end(); ++iter)
		{
			limiter = min
			(
				limiter,
				Scheme(mesh, faceFlux_, *this).limiter(*iter())
			);
		}

		weights_ =
			limiter * mesh.surfaceInterpolation::weights()
			+ (scalar(1) - limiter)*upwind<Type>(mesh, faceFlux_).weights();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //