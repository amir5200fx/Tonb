#include <fvmD2dt2.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <d2dt2Scheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvm
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<fvMatrix<Type> >
			d2dt2
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().d2dt2Scheme(name)
			)().fvmD2dt2(vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			d2dt2
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().d2dt2Scheme(name)
			)().fvmD2dt2(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			d2dt2
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::d2dt2Scheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().d2dt2Scheme(name)
			)().fvmD2dt2(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			d2dt2
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::d2dt2(vf, "d2dt2(" + vf.name() + ')');
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			d2dt2
			(
				const dimensionedScalar& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::d2dt2(rho, vf, "d2dt2(" + rho.name() + ',' + vf.name() + ')');
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			d2dt2
			(
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::d2dt2(rho, vf, "d2dt2(" + rho.name() + ',' + vf.name() + ')');
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvm

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //