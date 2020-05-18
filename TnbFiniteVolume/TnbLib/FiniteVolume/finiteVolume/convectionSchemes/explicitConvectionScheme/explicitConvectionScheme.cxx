#include <explicitConvectionScheme.hxx>

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
			explicitConvectionScheme<Type>::interpolate
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return tinterpScheme_().interpolate(vf);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			explicitConvectionScheme<Type>::flux
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return faceFlux * interpolate(faceFlux, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			explicitConvectionScheme<Type>::fvmDiv
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			tmp<fvMatrix<Type> > tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					faceFlux.dimensions()*vf.dimensions()
					)
			);
			fvMatrix<Type>& fvm = tfvm();

			// Matrix consistency
			fvm.diag() = 0;

			fvm += this->fvcDiv(faceFlux, vf);

			tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > tfaceFluxCorrection
				= faceFlux * interpolate(faceFlux, vf);

			const fvMesh& mesh = this->mesh();

			if (mesh.schemesDict().fluxRequired(vf.name()))
			{
				fvm.faceFluxCorrectionPtr() = tfaceFluxCorrection.ptr();
			}

			return tfvm;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			explicitConvectionScheme<Type>::fvcDiv
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