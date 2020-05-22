#include <fvcSurfaceIntegrate.hxx>

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
		void surfaceIntegrate
		(
			Field<Type>& ivf,
			const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf
		)
		{
			const fvMesh& mesh = ssf.mesh();

			const unallocLabelList& owner = mesh.owner();
			const unallocLabelList& neighbour = mesh.neighbour();

			const Field<Type>& issf = ssf;

			forAll(owner, facei)
			{
				ivf[owner[facei]] += issf[facei];
				ivf[neighbour[facei]] -= issf[facei];
			}

			forAll(mesh.boundary(), patchi)
			{
				const unallocLabelList& pFaceCells =
					mesh.boundary()[patchi].faceCells();

				const fvsPatchField<Type>& pssf = ssf.boundaryField()[patchi];

				forAll(mesh.boundary()[patchi], facei)
				{
					ivf[pFaceCells[facei]] += pssf[facei];
				}
			}

			ivf /= mesh.V();
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			surfaceIntegrate
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf
			)
		{
			const fvMesh& mesh = ssf.mesh();

			tmp<GeometricField<Type, fvPatchField, volMesh> > tvf
			(
				new GeometricField<Type, fvPatchField, volMesh>
				(
					IOobject
					(
						"surfaceIntegrate(" + ssf.name() + ')',
						ssf.instance(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					dimensioned<Type>
					(
						"0",
						ssf.dimensions() / dimVol,
						pTraits<Type>::zero
						),
					zeroGradientFvPatchField<Type>::typeName
					)
			);
			GeometricField<Type, fvPatchField, volMesh>& vf = tvf();

			surfaceIntegrate(vf.internalField(), ssf);
			vf.correctBoundaryConditions();

			return tvf;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			surfaceIntegrate
			(
				const tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >& tssf
			)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > tvf
			(
				fvc::surfaceIntegrate(tssf())
			);
			tssf.clear();
			return tvf;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> >
			surfaceSum
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf
			)
		{
			const fvMesh& mesh = ssf.mesh();

			tmp<GeometricField<Type, fvPatchField, volMesh> > tvf
			(
				new GeometricField<Type, fvPatchField, volMesh>
				(
					IOobject
					(
						"surfaceSum(" + ssf.name() + ')',
						ssf.instance(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					dimensioned<Type>("0", ssf.dimensions(), pTraits<Type>::zero),
					zeroGradientFvPatchField<Type>::typeName
					)
			);
			GeometricField<Type, fvPatchField, volMesh>& vf = tvf();

			const unallocLabelList& owner = mesh.owner();
			const unallocLabelList& neighbour = mesh.neighbour();

			forAll(owner, facei)
			{
				vf[owner[facei]] += ssf[facei];
				vf[neighbour[facei]] += ssf[facei];
			}

			forAll(mesh.boundary(), patchi)
			{
				const unallocLabelList& pFaceCells =
					mesh.boundary()[patchi].faceCells();

				const fvsPatchField<Type>& pssf = ssf.boundaryField()[patchi];

				forAll(mesh.boundary()[patchi], facei)
				{
					vf[pFaceCells[facei]] += pssf[facei];
				}
			}

			vf.correctBoundaryConditions();

			return tvf;
		}


		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> > surfaceSum
		(
			const tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >& tssf
		)
		{
			tmp<GeometricField<Type, fvPatchField, volMesh> > tvf = surfaceSum(tssf());
			tssf.clear();
			return tvf;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //