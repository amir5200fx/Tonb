#include <fvmGrad.hxx>

#include <gradScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvm
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename outerProduct<vector, Type>::type>
			> grad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf,
				const word& name
			)
		{
			return fv::gradScheme<Type>::New
			(
				vf.mesh(),
				vf.mesh().schemesDict().gradScheme(name)
			)().fvmGrad(vf);
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename outerProduct<vector, Type>::type>
			> grad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			)
		{
			return fvm::grad
			(
				vf,
				"grad(" + vf.name() + ')'
			);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvm

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //