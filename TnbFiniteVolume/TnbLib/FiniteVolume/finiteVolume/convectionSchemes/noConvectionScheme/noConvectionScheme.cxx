#include <noConvectionScheme.hxx>

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
			noConvectionScheme<Type>::interpolate
			(
				const surfaceScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
				(
					new GeometricField<Type, fvsPatchField, surfaceMesh>
					(
						IOobject
						(
							"interpolate(" + vf.name() + ')',
							vf.instance(),
							vf.db()
						),
						vf.mesh(),
						dimensioned<Type>
						(
							"0",
							vf.dimensions(),
							pTraits<Type>::zero
							)
						)
					);
		}


		template<class Type>
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			noConvectionScheme<Type>::flux
			(
				const surfaceScalarField& faceFlux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			return faceFlux * interpolate(faceFlux, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			noConvectionScheme<Type>::fvmDiv
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

			// Touch diagonal for consistency
			tfvm().diag() = 0;

			return tfvm;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			noConvectionScheme<Type>::fvcDiv
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