#include <fvmDdt.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <ddtScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvm
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<fvMatrix<Type> >
			ddt
			(
				GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().ddtScheme(name)
			)().fvmDdt(vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			ddt
			(
				const geometricOneField&,
				GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fvm::ddt(vf, name);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			ddt
			(
				const dimensionedScalar& rho,
				GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().ddtScheme(name)
			)().fvmDdt(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			ddt
			(
				const volScalarField& rho,
				GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::ddtScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().ddtScheme(name)
			)().fvmDdt(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			ddt
			(
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::ddt(vf, "ddt(" + vf.name() + ')');
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			ddt
			(
				const geometricOneField&,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::ddt(vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			ddt
			(
				const dimensionedScalar& rho,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::ddt(rho, vf, "ddt(" + rho.name() + ',' + vf.name() + ')');
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			ddt
			(
				const volScalarField& rho,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::ddt(rho, vf, "ddt(" + rho.name() + ',' + vf.name() + ')');
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvm

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //