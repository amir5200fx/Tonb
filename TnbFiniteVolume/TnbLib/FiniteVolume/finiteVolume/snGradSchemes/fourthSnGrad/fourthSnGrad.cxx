#include <fourthSnGrad.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <correctedSnGrad.hxx>
#include <linear.hxx>
#include <gaussGrad.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		fourthSnGrad<Type>::~fourthSnGrad()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			fourthSnGrad<Type>::correction
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			const fvMesh& mesh = this->mesh();

			tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > tcorr
			(
				(1.0 / 15.0)
				*(
					correctedSnGrad<Type>(mesh).snGrad(vf)
					- (linearInterpolate(gaussGrad<Type>(mesh).grad(vf)) & mesh.Sf())
					/ mesh.magSf()
					)
			);

			if (correctedSnGrad<Type>(mesh).corrected())
			{
				tcorr() += correctedSnGrad<Type>(mesh).correction(vf);
			}

			return tcorr;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //