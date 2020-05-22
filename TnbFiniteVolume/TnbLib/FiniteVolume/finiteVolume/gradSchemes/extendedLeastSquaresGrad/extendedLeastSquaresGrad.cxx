#include <extendedLeastSquaresGrad.hxx>

#include <extendedLeastSquaresVectors.hxx>
#include <gaussGrad.hxx>
#include <fvMesh.hxx>
#include <volMesh.hxx>
#include <surfaceMesh.hxx>
#include <GeometricField.hxx>
#include <zeroGradientFvPatchField.hxx>

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
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			extendedLeastSquaresGrad<Type>::calcGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vsf,
				const word& name
			) const
		{
			typedef typename outerProduct<vector, Type>::type GradType;

			const fvMesh& mesh = vsf.mesh();

			tmp<GeometricField<GradType, fvPatchField, volMesh> > tlsGrad
			(
				new GeometricField<GradType, fvPatchField, volMesh>
				(
					IOobject
					(
						name,
						vsf.instance(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					dimensioned<GradType>
					(
						"zero",
						vsf.dimensions() / dimLength,
						pTraits<GradType>::zero
						),
					zeroGradientFvPatchField<GradType>::typeName
					)
			);
			GeometricField<GradType, fvPatchField, volMesh>& lsGrad = tlsGrad();

			// Get reference to least square vectors
			const extendedLeastSquaresVectors& lsv = extendedLeastSquaresVectors::New
			(
				mesh,
				minDet_
			);

			const surfaceVectorField& ownLs = lsv.pVectors();
			const surfaceVectorField& neiLs = lsv.nVectors();

			const unallocLabelList& owner = mesh.owner();
			const unallocLabelList& neighbour = mesh.neighbour();

			forAll(owner, facei)
			{
				label own = owner[facei];
				label nei = neighbour[facei];

				Type deltaVsf = vsf[nei] - vsf[own];

				lsGrad[own] += ownLs[facei] * deltaVsf;
				lsGrad[nei] -= neiLs[facei] * deltaVsf;
			}

			// Boundary faces
			forAll(vsf.boundaryField(), patchi)
			{
				const fvsPatchVectorField& patchOwnLs = ownLs.boundaryField()[patchi];

				const unallocLabelList& faceCells =
					lsGrad.boundaryField()[patchi].patch().faceCells();

				if (vsf.boundaryField()[patchi].coupled())
				{
					Field<Type> neiVsf =
						vsf.boundaryField()[patchi].patchNeighbourField();

					forAll(neiVsf, patchFaceI)
					{
						lsGrad[faceCells[patchFaceI]] +=
							patchOwnLs[patchFaceI]
							* (neiVsf[patchFaceI] - vsf[faceCells[patchFaceI]]);
					}
				}
				else
				{
					const fvPatchField<Type>& patchVsf = vsf.boundaryField()[patchi];

					forAll(patchVsf, patchFaceI)
					{
						lsGrad[faceCells[patchFaceI]] +=
							patchOwnLs[patchFaceI]
							* (patchVsf[patchFaceI] - vsf[faceCells[patchFaceI]]);
					}
				}
			}


			const List<labelPair>& additionalCells = lsv.additionalCells();
			const vectorField& additionalVectors = lsv.additionalVectors();

			forAll(additionalCells, i)
			{
				lsGrad[additionalCells[i][0]] +=
					additionalVectors[i]
					* (vsf[additionalCells[i][1]] - vsf[additionalCells[i][0]]);
			}


			lsGrad.correctBoundaryConditions();
			gaussGrad<Type>::correctBoundaryConditions(vsf, lsGrad);

			return tlsGrad;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //