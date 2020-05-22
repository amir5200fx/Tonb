#include <limitedSnGrad.hxx>

#include <fv.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <correctedSnGrad.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		limitedSnGrad<Type>::~limitedSnGrad()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			limitedSnGrad<Type>::correction
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			GeometricField<Type, fvsPatchField, surfaceMesh> corr =
				correctedSnGrad<Type>(this->mesh()).correction(vf);

			surfaceScalarField limiter
			(
				min
				(
					limitCoeff_
					*mag(snGradScheme<Type>::snGrad(vf, deltaCoeffs(vf), "orthSnGrad"))
					/ (
					(1 - limitCoeff_)*mag(corr)
						+ dimensionedScalar("small", corr.dimensions(), SMALL)
						),
					dimensionedScalar("one", dimless, 1.0)
				)
			);

			if (fv::debug)
			{
				Info << "limitedSnGrad :: limiter min: " << min(limiter.internalField())
					<< " max: " << max(limiter.internalField())
					<< " avg: " << average(limiter.internalField()) << endl;
			}

			return limiter * corr;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //