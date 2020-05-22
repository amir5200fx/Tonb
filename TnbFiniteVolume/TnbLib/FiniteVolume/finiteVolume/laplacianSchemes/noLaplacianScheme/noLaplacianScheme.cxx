#include <noLaplacianScheme.hxx>

#include <surfaceInterpolate.hxx>
#include <fvcDiv.hxx>
#include <fvcGrad.hxx>
#include <fvMatrices.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			noLaplacianScheme<Type, GType>::fvcLaplacian
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			const surfaceScalarField& deltaCoeffs = this->mesh().deltaCoeffs();
			const surfaceScalarField& magSf = this->mesh().magSf();

			return tmp<GeometricField<Type, fvPatchField, volMesh> >
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"laplacian(" + vf.name() + ')',
							vf.instance(),
							vf.db()
						),
						vf.mesh(),
						dimensioned<Type>
						(
							"0",
							deltaCoeffs.dimensions()*magSf.dimensions()*vf.dimensions(),
							pTraits<Type>::zero
							)
						)
					);
		}


		template<class Type, class GType>
		tmp<fvMatrix<Type> >
			noLaplacianScheme<Type, GType>::fvmLaplacian
			(
				const GeometricField<GType, fvsPatchField, surfaceMesh>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			const surfaceScalarField& deltaCoeffs = this->mesh().deltaCoeffs();
			const surfaceScalarField& magSf = this->mesh().magSf();

			tmp<fvMatrix<Type> > tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					deltaCoeffs.dimensions()*gamma.dimensions()*
					magSf.dimensions()*vf.dimensions()
					)
			);

			// Create dummy diagonal
			tfvm().diag() = 0;

			return tfvm;
		}


		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			noLaplacianScheme<Type, GType>::fvcLaplacian
			(
				const GeometricField<GType, fvsPatchField, surfaceMesh>& gamma,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			const surfaceScalarField& deltaCoeffs = this->mesh().deltaCoeffs();
			const surfaceScalarField& magSf = this->mesh().magSf();

			return tmp<GeometricField<Type, fvPatchField, volMesh> >
				(
					new GeometricField<Type, fvPatchField, volMesh>
					(
						IOobject
						(
							"laplacian(" + vf.name() + ')',
							vf.instance(),
							vf.db()
						),
						vf.mesh(),
						dimensioned<Type>
						(
							"0",
							deltaCoeffs.dimensions()*gamma.dimensions()*
							magSf.dimensions()*vf.dimensions(),
							pTraits<Type>::zero
							)
						)
					);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //