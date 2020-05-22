#include <noAdjConvectionScheme.hxx>

#include <fvcSurfaceIntegrate.hxx>
#include <fvMatrices.hxx>
#include <fvcGrad.hxx>
#include <volMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<fvMatrix<Type> >
			noAdjConvectionScheme<Type>::fvmAdjDiv
			(
				const volVectorField& Up,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			tmp<fvMatrix<Type> > tfvm
			(
				new fvMatrix<Type>
				(
					vf,
					dimVol*Up.dimensions()*vf.dimensions() / dimLength
					)
			);

			// Touch diagonal for consistency
			tfvm().diag() = 0;

			return tfvm;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			noAdjConvectionScheme<Type>::fvcAdjDiv
			(
				const volVectorField& Up,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > tAdjConvection
			(
				fvc::grad(vf) & Up
			);

			tAdjConvection().rename
			(
				"adjConvection(" + Up.name() + ',' + vf.name() + ')'
			);

			return tAdjConvection;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //