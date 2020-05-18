#include <gaussConvectionScheme.hxx>

#include <fvcSurfaceIntegrate.hxx>
#include <fvMatrices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			gaussConvectionScheme<Type>::interpolate
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return tinterpScheme_().interpolate(vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			gaussConvectionScheme<Type>::flux
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return faceFlux * interpolate(faceFlux, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			gaussConvectionScheme<Type>::fvmDiv
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			tmp<surfaceScalarField> tweights = tinterpScheme_().weights(vf);
			const surfaceScalarField& weights = tweights();

			tmp<fvMatrix<Type> > tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					faceFlux.dimensions()*vf.dimensions()
					)
			);
			fvMatrix<Type>& fvm = tfvm();

			fvm.lower() = -weights.internalField()*faceFlux.internalField();
			fvm.upper() = fvm.lower() + faceFlux.internalField();
			fvm.negSumDiag();

			forAll(fvm.psi().boundaryField(), patchI)
			{
				const fvPatchField<Type>& psf = fvm.psi().boundaryField()[patchI];
				const fvsPatchScalarField& patchFlux = faceFlux.boundaryField()[patchI];
				const fvsPatchScalarField& pw = weights.boundaryField()[patchI];

				fvm.internalCoeffs()[patchI] = patchFlux * psf.valueInternalCoeffs(pw);
				fvm.boundaryCoeffs()[patchI] = -patchFlux * psf.valueBoundaryCoeffs(pw);
			}

			if (tinterpScheme_().corrected())
			{
				fvm += fvc::surfaceIntegrate(faceFlux*tinterpScheme_().correction(vf));
			}

			return tfvm;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			gaussConvectionScheme<Type>::fvcDiv
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > tConvection
			(
				fvc::surfaceIntegrate(flux(faceFlux, vf))
			);

			tConvection().rename
			(
				"convection(" + faceFlux.name() + ',' + vf.name() + ')'
			);

			return tConvection;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //