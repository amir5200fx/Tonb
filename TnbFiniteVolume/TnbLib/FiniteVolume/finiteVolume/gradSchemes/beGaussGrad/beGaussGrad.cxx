#include <beGaussGrad.hxx>

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
			beGaussGrad<Type>::calcGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vsf,
				const word& name
			) const
		{
			typedef typename outerProduct<vector, Type>::type GradType;

			tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > tssf =
				tinterpScheme_().interpolate(vsf);

			const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf = tssf();

			typedef typename outerProduct<vector, Type>::type GradType;

			const fvMesh& mesh = ssf.mesh();

			tmp<GeometricField<GradType, fvPatchField, volMesh> > tgGrad
			(
				new GeometricField<GradType, fvPatchField, volMesh>
				(
					IOobject
					(
						name,
						ssf.instance(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					dimensioned<GradType>
					(
						"0",
						ssf.dimensions() / dimLength,
						pTraits<GradType>::zero
						),
					zeroGradientFvPatchField<GradType>::typeName
					)
			);
			GeometricField<GradType, fvPatchField, volMesh>& gGrad = tgGrad();

			const unallocLabelList& owner = mesh.owner();
			const unallocLabelList& neighbour = mesh.neighbour();
			const vectorField& Sf = mesh.Sf();

			Field<GradType>& igGrad = gGrad;
			const Field<Type>& issf = ssf;

			// Calculate the gradient on the internal field
			forAll(owner, facei)
			{
				GradType Sfssf = Sf[facei] * issf[facei];

				igGrad[owner[facei]] += Sfssf;
				igGrad[neighbour[facei]] -= Sfssf;
			}

			// Assemble boundary contribution
			// If a patch is coupled or fixes value, regular gradient calculation
			// is used.  For all other patch types, one-sided implicit extrapolation
			// is applied instead.  HJ, 18/Sep/2006 Experimental!

			tensorField bct(mesh.V().field()*tensor(sphericalTensor::I));
			const vectorField& Cin = mesh.C();
			const Field<Type>& vsfIn = vsf.internalField();

			forAll(mesh.boundary(), patchi)
			{
				const unallocLabelList& pFaceCells =
					mesh.boundary()[patchi].faceCells();

				const vectorField& pSf = mesh.Sf().boundaryField()[patchi];
				const vectorField& pfC = mesh.C().boundaryField()[patchi];

				if
					(
						vsf.boundaryField()[patchi].coupled()
						|| vsf.boundaryField()[patchi].fixesValue()
						)
				{
					// Regular calculation, using patch value
					const fvsPatchField<Type>& pssf = ssf.boundaryField()[patchi];

					forAll(mesh.boundary()[patchi], facei)
					{
						igGrad[pFaceCells[facei]] += pSf[facei] * pssf[facei];
					}
				}
				else
				{
					// One-sided implicit extrapolation, using cell value
					forAll(mesh.boundary()[patchi], facei)
					{
						igGrad[pFaceCells[facei]] +=
							pSf[facei] * vsfIn[pFaceCells[facei]];

						// Accumulate face dot products for inversion
						bct[pFaceCells[facei]] -=
							pSf[facei] * (pfC[facei] - Cin[pFaceCells[facei]]);
					}
				}
			}

			// Calculate corrected gradient and evaluate boundary values
			// Note: boundary correction for forced snGrad is removed
			// HJ, 19/Sep/2006
			igGrad = (igGrad & inv(bct));
			gGrad.correctBoundaryConditions();

			return tgGrad;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //