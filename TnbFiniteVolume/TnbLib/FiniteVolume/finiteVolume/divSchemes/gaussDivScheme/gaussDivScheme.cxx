#include <gaussDivScheme.hxx>

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
		tmp
			<
			GeometricField
			<typename innerProduct<vector, Type>::type, fvPatchField, volMesh>
			>
			gaussDivScheme<Type>::fvcDiv
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			tmp
				<
				GeometricField
				<typename innerProduct<vector, Type>::type, fvPatchField, volMesh>
				> tDiv
				(
					fvc::surfaceIntegrate
					(
						this->mesh_.Sf() & this->tinterpScheme_().interpolate(vf)
					)
				);

			tDiv().rename("div(" + vf.name() + ')');

			return tDiv;
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
			> gaussDivScheme<Type>::fvmUDiv
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			FatalErrorIn
			(
				"tmp<BlockLduSystem> gaussDivScheme<Type>::fvmUDiv\n"
				"(\n"
				"    GeometricField<Type, fvPatchField, volMesh>&"
				")\n"
			) << "Implicit div operator defined only for vector."
				<< abort(FatalError);

			typedef typename innerProduct<vector, Type>::type DivType;

			tmp<BlockLduSystem<vector, DivType> > tbs
			(
				new BlockLduSystem<vector, DivType>(vf.mesh())
			);

			return tbs;
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename innerProduct<vector, Type>::type>
			> gaussDivScheme<Type>::fvmUDiv
			(
				const surfaceScalarField& flux,
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			FatalErrorIn
			(
				"tmp<BlockLduSystem> gaussDivScheme<Type>::fvmUDiv\n"
				"(\n"
				"    const surfaceScalarField& flux"
				"    const GeometricField<Type, fvPatchField, volMesh>&"
				")\n"
			) << "Implicit div operator defined only for vector."
				<< abort(FatalError);

			typedef typename innerProduct<vector, Type>::type DivType;

			tmp<BlockLduSystem<vector, DivType> > tbs
			(
				new BlockLduSystem<vector, DivType>(vf.mesh())
			);

			return tbs;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //