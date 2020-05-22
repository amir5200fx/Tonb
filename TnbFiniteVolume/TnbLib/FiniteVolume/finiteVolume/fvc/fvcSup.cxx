#include <fvcSup.hxx>

#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			Su
			(
				const GeometricField<Type, fvPatchField, volMesh>& su,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return su;
		}

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			Su
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh> >& tsu,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tsu;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			Sp
			(
				const volScalarField& sp,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return sp * vf;
		}

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			Sp
			(
				const tmp<volScalarField>& tsp,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tsp * vf;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			Sp
			(
				const dimensionedScalar& sp,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return sp * vf;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			SuSp
			(
				const volScalarField& sp,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return sp * vf;
		}

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			SuSp
			(
				const tmp<volScalarField>& tsp,
				GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return tsp * vf;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //