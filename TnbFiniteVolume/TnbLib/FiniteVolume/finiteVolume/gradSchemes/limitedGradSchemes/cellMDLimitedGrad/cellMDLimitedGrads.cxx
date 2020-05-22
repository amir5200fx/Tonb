#include <cellMDLimitedGrad.hxx>

#include <gaussGrad.hxx>
#include <fvMesh.hxx>
#include <volMesh.hxx>
#include <surfaceMesh.hxx>
#include <volFields.hxx>
#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		makeFvGradScheme(cellMDLimitedGrad)

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			template<>
		tmp<volVectorField> cellMDLimitedGrad<scalar>::calcGrad
		(
			const volScalarField& vsf,
			const word& name
		) const
		{
			const fvMesh& mesh = vsf.mesh();

			tmp<volVectorField> tGrad = basicGradScheme_().calcGrad(vsf, name);

			if (k_ < SMALL)
			{
				return tGrad;
			}

			volVectorField& g = tGrad();

			const unallocLabelList& owner = mesh.owner();
			const unallocLabelList& neighbour = mesh.neighbour();

			const volVectorField& C = mesh.C();
			const surfaceVectorField& Cf = mesh.Cf();

			scalarField maxVsf(vsf.internalField());
			scalarField minVsf(vsf.internalField());

			forAll(owner, facei)
			{
				label own = owner[facei];
				label nei = neighbour[facei];

				scalar vsfOwn = vsf[own];
				scalar vsfNei = vsf[nei];

				maxVsf[own] = max(maxVsf[own], vsfNei);
				minVsf[own] = min(minVsf[own], vsfNei);

				maxVsf[nei] = max(maxVsf[nei], vsfOwn);
				minVsf[nei] = min(minVsf[nei], vsfOwn);
			}


			const volScalarField::GeometricBoundaryField& bsf = vsf.boundaryField();

			forAll(bsf, patchi)
			{
				const fvPatchScalarField& psf = bsf[patchi];

				const unallocLabelList& pOwner = mesh.boundary()[patchi].faceCells();

				if (psf.coupled())
				{
					scalarField psfNei = psf.patchNeighbourField();

					forAll(pOwner, pFacei)
					{
						label own = pOwner[pFacei];
						scalar vsfNei = psfNei[pFacei];

						maxVsf[own] = max(maxVsf[own], vsfNei);
						minVsf[own] = min(minVsf[own], vsfNei);
					}
				}
				else
				{
					forAll(pOwner, pFacei)
					{
						label own = pOwner[pFacei];
						scalar vsfNei = psf[pFacei];

						maxVsf[own] = max(maxVsf[own], vsfNei);
						minVsf[own] = min(minVsf[own], vsfNei);
					}
				}
			}

			maxVsf -= vsf;
			minVsf -= vsf;

			if (k_ < 1.0)
			{
				scalarField maxMinVsf = (1.0 / k_ - 1.0)*(maxVsf - minVsf);
				maxVsf += maxMinVsf;
				minVsf -= maxMinVsf;

				//maxVsf *= 1.0/k_;
				//minVsf *= 1.0/k_;
			}


			forAll(owner, facei)
			{
				label own = owner[facei];
				label nei = neighbour[facei];

				// owner side
				limitFace
				(
					g[own],
					maxVsf[own],
					minVsf[own],
					Cf[facei] - C[own]
				);

				// neighbour side
				limitFace
				(
					g[nei],
					maxVsf[nei],
					minVsf[nei],
					Cf[facei] - C[nei]
				);
			}


			forAll(bsf, patchi)
			{
				const unallocLabelList& pOwner = mesh.boundary()[patchi].faceCells();
				const vectorField& pCf = Cf.boundaryField()[patchi];

				forAll(pOwner, pFacei)
				{
					label own = pOwner[pFacei];

					limitFace
					(
						g[own],
						maxVsf[own],
						minVsf[own],
						pCf[pFacei] - C[own]
					);
				}
			}

			g.correctBoundaryConditions();
			gaussGrad<scalar>::correctBoundaryConditions(vsf, g);

			return tGrad;
		}


		template<>
		tmp<volTensorField> cellMDLimitedGrad<vector>::calcGrad
		(
			const volVectorField& vsf,
			const word& name
		) const
		{
			const fvMesh& mesh = vsf.mesh();

			tmp<volTensorField> tGrad = basicGradScheme_().calcGrad(vsf, name);

			if (k_ < SMALL)
			{
				return tGrad;
			}

			volTensorField& g = tGrad();

			const unallocLabelList& owner = mesh.owner();
			const unallocLabelList& neighbour = mesh.neighbour();

			const volVectorField& C = mesh.C();
			const surfaceVectorField& Cf = mesh.Cf();

			vectorField maxVsf(vsf.internalField());
			vectorField minVsf(vsf.internalField());

			forAll(owner, facei)
			{
				label own = owner[facei];
				label nei = neighbour[facei];

				const vector& vsfOwn = vsf[own];
				const vector& vsfNei = vsf[nei];

				maxVsf[own] = max(maxVsf[own], vsfNei);
				minVsf[own] = min(minVsf[own], vsfNei);

				maxVsf[nei] = max(maxVsf[nei], vsfOwn);
				minVsf[nei] = min(minVsf[nei], vsfOwn);
			}


			const volVectorField::GeometricBoundaryField& bsf = vsf.boundaryField();

			forAll(bsf, patchi)
			{
				const fvPatchVectorField& psf = bsf[patchi];
				const unallocLabelList& pOwner = mesh.boundary()[patchi].faceCells();

				if (psf.coupled())
				{
					vectorField psfNei = psf.patchNeighbourField();

					forAll(pOwner, pFacei)
					{
						label own = pOwner[pFacei];
						const vector& vsfNei = psfNei[pFacei];

						maxVsf[own] = max(maxVsf[own], vsfNei);
						minVsf[own] = min(minVsf[own], vsfNei);
					}
				}
				else
				{
					forAll(pOwner, pFacei)
					{
						label own = pOwner[pFacei];
						const vector& vsfNei = psf[pFacei];

						maxVsf[own] = max(maxVsf[own], vsfNei);
						minVsf[own] = min(minVsf[own], vsfNei);
					}
				}
			}

			maxVsf -= vsf;
			minVsf -= vsf;

			if (k_ < 1.0)
			{
				vectorField maxMinVsf = (1.0 / k_ - 1.0)*(maxVsf - minVsf);
				maxVsf += maxMinVsf;
				minVsf -= maxMinVsf;

				//maxVsf *= 1.0/k_;
				//minVsf *= 1.0/k_;
			}


			forAll(owner, facei)
			{
				label own = owner[facei];
				label nei = neighbour[facei];

				// owner side
				limitFace
				(
					g[own],
					maxVsf[own],
					minVsf[own],
					Cf[facei] - C[own]
				);

				// neighbour side
				limitFace
				(
					g[nei],
					maxVsf[nei],
					minVsf[nei],
					Cf[facei] - C[nei]
				);
			}


			forAll(bsf, patchi)
			{
				const unallocLabelList& pOwner = mesh.boundary()[patchi].faceCells();
				const vectorField& pCf = Cf.boundaryField()[patchi];

				forAll(pOwner, pFacei)
				{
					label own = pOwner[pFacei];

					limitFace
					(
						g[own],
						maxVsf[own],
						minVsf[own],
						pCf[pFacei] - C[own]
					);
				}
			}

			g.correctBoundaryConditions();
			gaussGrad<vector>::correctBoundaryConditions(vsf, g);

			return tGrad;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //