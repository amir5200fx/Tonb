#include <faceMDLimitedGrad.hxx>

#include <cellMDLimitedGrad.hxx>
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

		makeFvGradScheme(faceMDLimitedGrad)

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			// FaceLimited scalar gradient
			template<>
		tmp<volVectorField> faceMDLimitedGrad<scalar>::calcGrad
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

			scalar rk = (1.0 / k_ - 1.0);

			forAll(owner, facei)
			{
				label own = owner[facei];
				label nei = neighbour[facei];

				scalar vsfOwn = vsf[own];
				scalar vsfNei = vsf[nei];

				scalar maxFace = max(vsfOwn, vsfNei);
				scalar minFace = min(vsfOwn, vsfNei);

				if (k_ < 1.0)
				{
					scalar maxMinFace = rk * (maxFace - minFace);
					maxFace += maxMinFace;
					minFace -= maxMinFace;
				}

				// owner side
				cellMDLimitedGrad<scalar>::limitFace
				(
					g[own],
					maxFace - vsfOwn,
					minFace - vsfOwn,
					Cf[facei] - C[own]
				);

				// neighbour side
				cellMDLimitedGrad<scalar>::limitFace
				(
					g[nei],
					maxFace - vsfNei,
					minFace - vsfNei,
					Cf[facei] - C[nei]
				);
			}

			const volScalarField::GeometricBoundaryField& bsf = vsf.boundaryField();

			forAll(bsf, patchi)
			{
				const fvPatchScalarField& psf = bsf[patchi];

				const unallocLabelList& pOwner = mesh.boundary()[patchi].faceCells();
				const vectorField& pCf = Cf.boundaryField()[patchi];

				if (psf.coupled())
				{
					scalarField psfNei = psf.patchNeighbourField();

					forAll(pOwner, pFacei)
					{
						label own = pOwner[pFacei];

						scalar vsfOwn = vsf[own];
						scalar vsfNei = psfNei[pFacei];

						scalar maxFace = max(vsfOwn, vsfNei);
						scalar minFace = min(vsfOwn, vsfNei);

						if (k_ < 1.0)
						{
							scalar maxMinFace = rk * (maxFace - minFace);
							maxFace += maxMinFace;
							minFace -= maxMinFace;
						}

						cellMDLimitedGrad<scalar>::limitFace
						(
							g[own],
							maxFace - vsfOwn,
							minFace - vsfOwn,
							pCf[pFacei] - C[own]
						);
					}
				}
				else if (psf.fixesValue())
				{
					forAll(pOwner, pFacei)
					{
						label own = pOwner[pFacei];

						scalar vsfOwn = vsf[own];
						scalar vsfNei = psf[pFacei];

						scalar maxFace = max(vsfOwn, vsfNei);
						scalar minFace = min(vsfOwn, vsfNei);

						if (k_ < 1.0)
						{
							scalar maxMinFace = rk * (maxFace - minFace);
							maxFace += maxMinFace;
							minFace -= maxMinFace;
						}

						cellMDLimitedGrad<scalar>::limitFace
						(
							g[own],
							maxFace - vsfOwn,
							minFace - vsfOwn,
							pCf[pFacei] - C[own]
						);
					}
				}
			}

			g.correctBoundaryConditions();
			gradScheme<scalar>::correctBoundaryConditions(vsf, g);

			return tGrad;
		}


		template<>
		tmp<volTensorField> faceMDLimitedGrad<vector>::calcGrad
		(
			const volVectorField& vvf,
			const word& name
		) const
		{
			const fvMesh& mesh = vvf.mesh();

			tmp<volTensorField> tGrad = basicGradScheme_().calcGrad(vvf, name);

			if (k_ < SMALL)
			{
				return tGrad;
			}

			volTensorField& g = tGrad();

			const unallocLabelList& owner = mesh.owner();
			const unallocLabelList& neighbour = mesh.neighbour();

			const volVectorField& C = mesh.C();
			const surfaceVectorField& Cf = mesh.Cf();

			scalar rk = (1.0 / k_ - 1.0);

			forAll(owner, facei)
			{
				label own = owner[facei];
				label nei = neighbour[facei];

				vector vvfOwn = vvf[own];
				vector vvfNei = vvf[nei];

				vector maxFace = max(vvfOwn, vvfNei);
				vector minFace = min(vvfOwn, vvfNei);

				if (k_ < 1.0)
				{
					vector maxMinFace = rk * (maxFace - minFace);
					maxFace += maxMinFace;
					minFace -= maxMinFace;
				}

				// owner side
				cellMDLimitedGrad<vector>::limitFace
				(
					g[own],
					maxFace - vvfOwn,
					minFace - vvfOwn,
					Cf[facei] - C[nei]
				);


				// neighbour side
				cellMDLimitedGrad<vector>::limitFace
				(
					g[nei],
					maxFace - vvfNei,
					minFace - vvfNei,
					Cf[facei] - C[nei]
				);
			}


			const volVectorField::GeometricBoundaryField& bvf = vvf.boundaryField();

			forAll(bvf, patchi)
			{
				const fvPatchVectorField& psf = bvf[patchi];

				const unallocLabelList& pOwner = mesh.boundary()[patchi].faceCells();
				const vectorField& pCf = Cf.boundaryField()[patchi];

				if (psf.coupled())
				{
					vectorField psfNei = psf.patchNeighbourField();

					forAll(pOwner, pFacei)
					{
						label own = pOwner[pFacei];

						vector vvfOwn = vvf[own];
						vector vvfNei = psfNei[pFacei];

						vector maxFace = max(vvfOwn, vvfNei);
						vector minFace = min(vvfOwn, vvfNei);

						if (k_ < 1.0)
						{
							vector maxMinFace = rk * (maxFace - minFace);
							maxFace += maxMinFace;
							minFace -= maxMinFace;
						}

						cellMDLimitedGrad<vector>::limitFace
						(
							g[own],
							maxFace - vvfOwn, minFace - vvfOwn,
							pCf[pFacei] - C[own]
						);
					}
				}
				else if (psf.fixesValue())
				{
					forAll(pOwner, pFacei)
					{
						label own = pOwner[pFacei];

						vector vvfOwn = vvf[own];
						vector vvfNei = psf[pFacei];

						vector maxFace = max(vvfOwn, vvfNei);
						vector minFace = min(vvfOwn, vvfNei);

						if (k_ < 1.0)
						{
							vector maxMinFace = rk * (maxFace - minFace);
							maxFace += maxMinFace;
							minFace -= maxMinFace;
						}

						cellMDLimitedGrad<vector>::limitFace
						(
							g[own],
							maxFace - vvfOwn,
							minFace - vvfOwn,
							pCf[pFacei] - C[own]
						);
					}
				}
			}

			g.correctBoundaryConditions();
			gradScheme<vector>::correctBoundaryConditions(vvf, g);

			return tGrad;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //