#include <explicitAdjConvectionScheme.hxx>

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
			explicitAdjConvectionScheme<Type>::fvmAdjDiv
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
			fvMatrix<Type>& fvm = tfvm();

			// Matrix consistency
			fvm.diag() = 0;

			fvm += this->fvcAdjDiv(Up, vf);

			return tfvm;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			explicitAdjConvectionScheme<Type>::fvcAdjDiv
			(
				const volVectorField& Up,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			// Return Up & grad(vf).T()
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