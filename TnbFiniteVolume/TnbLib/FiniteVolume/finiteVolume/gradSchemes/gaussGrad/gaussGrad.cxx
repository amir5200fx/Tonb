#include <gaussGrad.hxx>

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
			gaussGrad<Type>::gradf
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf,
				const word& name
			)
		{
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

			forAll(owner, facei)
			{
				GradType Sfssf = Sf[facei] * issf[facei];

				igGrad[owner[facei]] += Sfssf;
				igGrad[neighbour[facei]] -= Sfssf;
			}

			forAll(mesh.boundary(), patchi)
			{
				const unallocLabelList& pFaceCells =
					mesh.boundary()[patchi].faceCells();

				const vectorField& pSf = mesh.Sf().boundaryField()[patchi];

				const fvsPatchField<Type>& pssf = ssf.boundaryField()[patchi];

				forAll(mesh.boundary()[patchi], facei)
				{
					igGrad[pFaceCells[facei]] += pSf[facei] * pssf[facei];
				}
			}

			igGrad /= mesh.V();

			gGrad.correctBoundaryConditions();

			return tgGrad;
		}


		template<class Type>
		tmp
			<
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>
			>
			gaussGrad<Type>::calcGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vsf,
				const word& name
			) const
		{
			typedef typename outerProduct<vector, Type>::type GradType;

			tmp<GeometricField<GradType, fvPatchField, volMesh> > tgGrad
			(
				gradf(tinterpScheme_().interpolate(vsf), name)
			);
			GeometricField<GradType, fvPatchField, volMesh>& gGrad = tgGrad();

			gGrad.rename("grad(" + vsf.name() + ')');
			this->correctBoundaryConditions(vsf, gGrad);

			return tgGrad;
		}

		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename outerProduct<vector, Type>::type>
			> gaussGrad<Type>::fvmGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			FatalErrorIn
			(
				"tmp<BlockLduSystem> fvmGrad\n"
				"(\n"
				"    GeometricField<Type, fvPatchField, volMesh>&"
				")\n"
			) << "Implicit gradient operator defined only for scalar."
				<< abort(FatalError);

			typedef typename outerProduct<vector, Type>::type GradType;

			tmp<BlockLduSystem<vector, GradType> > tbs
			(
				new BlockLduSystem<vector, GradType>(vf.mesh())
			);

			return tbs;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //