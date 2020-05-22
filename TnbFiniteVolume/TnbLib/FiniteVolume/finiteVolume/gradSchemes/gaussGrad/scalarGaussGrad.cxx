#include <gaussGrad.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		template<>
		tmp<BlockLduSystem<vector, vector> > gaussGrad<scalar>::fvmGrad
		(
			const GeometricField<scalar, fvPatchField, volMesh>& vf
		) const
		{
			tmp<surfaceScalarField> tweights = this->tinterpScheme_().weights(vf);
			const scalarField& wIn = tweights().internalField();

			const fvMesh& mesh = vf.mesh();

			tmp<BlockLduSystem<vector, vector> > tbs
			(
				new BlockLduSystem<vector, vector>(mesh)
			);
			BlockLduSystem<vector, vector>& bs = tbs();
			vectorField& source = bs.source();

			// Grab ldu parts of block matrix as linear always
			CoeffField<vector>::linearTypeField& d = bs.diag().asLinear();
			CoeffField<vector>::linearTypeField& u = bs.upper().asLinear();
			CoeffField<vector>::linearTypeField& l = bs.lower().asLinear();

			const vectorField& SfIn = mesh.Sf().internalField();

			l = -wIn * SfIn;
			u = l + SfIn;
			bs.negSumDiag();

			// Boundary contributions
			forAll(vf.boundaryField(), patchI)
			{
				const fvPatchScalarField& pf = vf.boundaryField()[patchI];
				const fvPatch& patch = pf.patch();
				const vectorField& pSf = patch.Sf();
				const fvsPatchScalarField& pw = tweights().boundaryField()[patchI];
				const labelList& fc = patch.faceCells();

				const scalarField internalCoeffs(pf.valueInternalCoeffs(pw));

				// Diag contribution
				forAll(pf, faceI)
				{
					d[fc[faceI]] += internalCoeffs[faceI] * pSf[faceI];
				}

				if (patch.coupled())
				{
					CoeffField<vector>::linearTypeField& pcoupleUpper =
						bs.coupleUpper()[patchI].asLinear();
					CoeffField<vector>::linearTypeField& pcoupleLower =
						bs.coupleLower()[patchI].asLinear();

					const vectorField pcl = -pw * pSf;
					const vectorField pcu = pcl + pSf;

					// Coupling  contributions
					pcoupleLower -= pcl;
					pcoupleUpper -= pcu;
				}
				else
				{
					const scalarField boundaryCoeffs(pf.valueBoundaryCoeffs(pw));

					// Boundary contribution
					forAll(pf, faceI)
					{
						source[fc[faceI]] -= boundaryCoeffs[faceI] * pSf[faceI];
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