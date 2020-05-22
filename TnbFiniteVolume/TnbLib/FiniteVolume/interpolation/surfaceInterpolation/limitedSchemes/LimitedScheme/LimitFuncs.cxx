#include <LimitFuncs.hxx>

#include <objectRegistry.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace limitFuncs
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		inline tmp<volScalarField> magSqr<Type>::operator()
			(
				const GeometricField<Type, fvPatchField, volMesh>& phi
				) const
		{
			return tnbLib::magSqr(phi);
		}


		template<>
		inline tmp<volScalarField> magSqr<scalar>::operator()
			(
				const volScalarField& phi
				) const
		{
			return phi;
		}


		template<>
		inline tmp<volScalarField> magSqr<tensor>::operator()
			(
				const volTensorField& phi
				) const
		{
			return tnbLib::tr(phi);
		}


		template<class Type>
		inline tmp<volScalarField> rhoMagSqr<Type>::operator()
			(
				const GeometricField<Type, fvPatchField, volMesh>& phi
				) const
		{
			const volScalarField& rho =
				phi.db().objectRegistry::template
				lookupObject<volScalarField>("rho");

			return tnbLib::magSqr(phi / rho);
		}


		template<>
		inline tmp<volScalarField> rhoMagSqr<scalar>::operator()
			(
				const volScalarField& phi
				) const
		{
			const volScalarField& rho =
				phi.db().objectRegistry::lookupObject<volScalarField>("rho");

			return phi / rho;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace limitFuncs
} // End namespace tnbLib

// ************************************************************************* //