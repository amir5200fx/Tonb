#include <fvcReconstruct.hxx>

#include <fvMesh.hxx>
#include <zeroGradientFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			reconstruct
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf
			)
		{
			typedef typename outerProduct<vector, Type>::type GradType;

			const fvMesh& mesh = ssf.mesh();

			tmp<GeometricField<GradType, fvPatchField, volMesh> > treconField
			(
				new GeometricField<GradType, fvPatchField, volMesh>
				(
					IOobject
					(
						"volIntegrate(" + ssf.name() + ')',
						ssf.instance(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					ssf.dimensions() / dimArea,
					zeroGradientFvPatchField<GradType>::typeName
					)
			);
			GeometricField<GradType, fvPatchField, volMesh>& reconField =
				treconField();

			// Note:
			// 1) Reconstruction is only available in cell centres: there is no need
			//    to invert the tensor on the boundary
			// 2) For boundaries, the only reconstructed data is the flux times
			//    normal.  Based on this guess, boundary conditions can adjust
			//    patch values
			// HJ, 12/Aug/2011

			GeometricField<GradType, fvPatchField, volMesh> fluxTimesNormal =
				surfaceSum((mesh.Sf() / mesh.magSf())*ssf);

			// Note: hinv inverse must be used to stabilise the inverse on bad meshes
			// but it gives strange failures
			// HJ, 19/Aug/2015
			reconField.internalField() =
				(
					inv
					(
						surfaceSum(sqr(mesh.Sf()) / mesh.magSf())().internalField()
					)
					& fluxTimesNormal.internalField()
					);

			reconField.boundaryField() = fluxTimesNormal.boundaryField();

			treconField().correctBoundaryConditions();

			return treconField;
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			reconstruct
			(
				const tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >& tssf
			)
		{
			typedef typename outerProduct<vector, Type>::type GradType;
			tmp<GeometricField<GradType, fvPatchField, volMesh> > tvf
			(
				fvc::reconstruct(tssf())
			);
			tssf.clear();
			return tvf;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //