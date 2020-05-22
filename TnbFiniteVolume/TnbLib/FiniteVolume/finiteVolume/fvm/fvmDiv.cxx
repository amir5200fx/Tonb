#include <fvmDiv.hxx>

#include <fvMesh.hxx>
#include <convectionScheme.hxx>
#include <divScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvm
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<fvMatrix<Type> >
			div
			(
				const surfaceScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::convectionScheme<Type>::New
			(
				vf.mesh(),
				rho,
				vf.mesh().schemesDict().divScheme(name)
			)().fvmDiv(rho, vf);
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			div
			(
				const tmp<surfaceScalarField>& trho,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			tmp<fvMatrix<Type> > Div(fvm::div(trho(), vf, name));
			trho.clear();
			return Div;
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			div
			(
				const surfaceScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::div(rho, vf, "div(" + rho.name() + ',' + vf.name() + ')');
		}


		template<class Type>
		tmp<fvMatrix<Type> >
			div
			(
				const tmp<surfaceScalarField>& trho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp<fvMatrix<Type> > Div(fvm::div(trho(), vf));
			trho.clear();
			return Div;
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
			> UDiv
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::divScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().divScheme(name)
			)().fvmUDiv(vf);
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
			> UDiv
			(
				const surfaceScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::divScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().divScheme(name)
			)().fvmUDiv(rho, vf);
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
			> UDiv
			(
				const tmp<surfaceScalarField>& trho,
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			tmp
				<
				BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
				>
				Div(fvm::UDiv(trho(), vf, name));
			trho.clear();
			return Div;
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
			> UDiv
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::UDiv
			(
				vf,
				"div(" + vf.name() + ')'
			);
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
			> UDiv
			(
				const surfaceScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::UDiv
			(
				rho,
				vf,
				"div(" + rho.name() + ',' + vf.name() + ')'
			);
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
			> UDiv
			(
				const tmp<surfaceScalarField>& trho,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp
				<
				BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
				>
				Div(fvm::UDiv(trho(), vf));
			trho.clear();
			return Div;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvm

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //