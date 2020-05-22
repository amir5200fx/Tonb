#include <vectorGaussDivScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<>
		tmp<BlockLduSystem<vector, scalar> > gaussDivScheme<vector>::fvmUDiv
		(
			const GeometricField<vector, fvPatchField, volMesh>& vf
		) const
		{
			// Get weights
			surfaceScalarField weights = this->tinterpScheme_().weights(vf);

			const fvMesh& mesh = vf.mesh();

			tmp<BlockLduSystem<vector, scalar> > tbs
			(
				new BlockLduSystem<vector, scalar>(mesh)
			);
			BlockLduSystem<vector, scalar>& bs = tbs();
			scalarField& source = bs.source();

			// Grab ldu parts of block matrix as linear always
			CoeffField<vector>::linearTypeField& d = bs.diag().asLinear();
			CoeffField<vector>::linearTypeField& u = bs.upper().asLinear();
			CoeffField<vector>::linearTypeField& l = bs.lower().asLinear();

			// Internal field
			const vectorField& SfIn = mesh.Sf().internalField();
			const scalarField& wIn = weights.internalField();

			l = -wIn * SfIn;
			u = l + SfIn;
			bs.negSumDiag();

			// Boundary contributions
			forAll(vf.boundaryField(), patchI)
			{
				const fvPatchVectorField& pf = vf.boundaryField()[patchI];
				const fvPatch& patch = pf.patch();
				const vectorField& Sf = patch.Sf();
				const fvsPatchScalarField& pw = weights.boundaryField()[patchI];
				const unallocLabelList& fc = patch.faceCells();

				const vectorField internalCoeffs(pf.valueInternalCoeffs(pw));

				// Diag contribution
				forAll(pf, faceI)
				{
					d[fc[faceI]] += cmptMultiply(internalCoeffs[faceI], Sf[faceI]);
				}

				if (patch.coupled())
				{
					CoeffField<vector>::linearTypeField& pcoupleUpper =
						bs.coupleUpper()[patchI].asLinear();
					CoeffField<vector>::linearTypeField& pcoupleLower =
						bs.coupleLower()[patchI].asLinear();

					const vectorField pcl = -pw * Sf;
					const vectorField pcu = pcl + Sf;

					// Coupling  contributions
					pcoupleLower -= pcl;
					pcoupleUpper -= pcu;
				}
				else
				{
					const vectorField boundaryCoeffs(pf.valueBoundaryCoeffs(pw));

					// Boundary contribution
					forAll(pf, faceI)
					{
						source[fc[faceI]] -= boundaryCoeffs[faceI] & Sf[faceI];
					}
				}
			}

			// Interpolation schemes with corrections not accounted for

			return tbs;
		}


		template<>
		tmp<BlockLduSystem<vector, scalar> > gaussDivScheme<vector>::fvmUDiv
		(
			const surfaceScalarField& flux,
			const GeometricField<vector, fvPatchField, volMesh>& vf
		) const
		{
			// Get weights
			surfaceScalarField weights = this->tinterpScheme_().weights(vf);

			const fvMesh& mesh = vf.mesh();

			tmp<BlockLduSystem<vector, scalar> > tbs
			(
				new BlockLduSystem<vector, scalar>(mesh)
			);
			BlockLduSystem<vector, scalar>& bs = tbs();
			scalarField& source = bs.source();

			// Grab ldu parts of block matrix as linear always
			CoeffField<vector>::linearTypeField& d = bs.diag().asLinear();
			CoeffField<vector>::linearTypeField& u = bs.upper().asLinear();
			CoeffField<vector>::linearTypeField& l = bs.lower().asLinear();

			// Internal field
			const vectorField& SfIn = mesh.Sf().internalField();
			const scalarField& wIn = weights.internalField();
			const scalarField& fluxIn = flux.internalField();

			l = -wIn * fluxIn*SfIn;
			u = l + fluxIn * SfIn;
			bs.negSumDiag();

			// Boundary contributions
			forAll(vf.boundaryField(), patchI)
			{
				const fvPatchVectorField& pf = vf.boundaryField()[patchI];
				const fvPatch& patch = pf.patch();
				const vectorField& Sf = patch.Sf();
				const fvsPatchScalarField& pw = weights.boundaryField()[patchI];
				const unallocLabelList& fc = patch.faceCells();

				const scalarField& pFlux = flux.boundaryField()[patchI];

				const vectorField internalCoeffs(pf.valueInternalCoeffs(pw));

				// Diag contribution
				forAll(pf, faceI)
				{
					d[fc[faceI]] += cmptMultiply
					(
						internalCoeffs[faceI],
						pFlux[faceI] * Sf[faceI]
					);
				}

				if (patch.coupled())
				{
					CoeffField<vector>::linearTypeField& pcoupleUpper =
						bs.coupleUpper()[patchI].asLinear();
					CoeffField<vector>::linearTypeField& pcoupleLower =
						bs.coupleLower()[patchI].asLinear();

					const vectorField pcl = -pw * pFlux*Sf;
					const vectorField pcu = pcl + pFlux * Sf;

					// Coupling  contributions
					pcoupleLower -= pcl;
					pcoupleUpper -= pcu;
				}
				else
				{
					const vectorField boundaryCoeffs(pf.valueBoundaryCoeffs(pw));

					// Boundary contribution
					forAll(pf, faceI)
					{
						source[fc[faceI]] -=
							(
								boundaryCoeffs[faceI] & (pFlux[faceI] * Sf[faceI])
								);
					}
				}
			}

			// Interpolation schemes with corrections not accounted for

			return tbs;
		}

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //