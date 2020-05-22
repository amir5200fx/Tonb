#include <singleCellFvMesh.hxx>

#include <tnbTime.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	tmp<GeometricField<Type, fvPatchField, volMesh> > singleCellFvMesh::interpolate
	(
		const GeometricField<Type, fvPatchField, volMesh>& vf
	) const
	{
		// Create internal-field values
		Field<Type> internalField(1, gAverage(vf));

		// Create and map the patch field values
		PtrList<fvPatchField<Type> > patchFields(vf.boundaryField().size());

		if (agglomerate())
		{
			forAll(vf.boundaryField(), patchI)
			{
				const labelList& agglom = patchFaceAgglomeration_[patchI];
				label nAgglom = max(agglom) + 1;

				// Use inverse of agglomeration. This is from agglomeration to
				// original (fine) mesh patch face.
				labelListList coarseToFine(invertOneToMany(nAgglom, agglom));
				inplaceReorder(patchFaceMap_[patchI], coarseToFine);
				scalarListList coarseWeights(nAgglom);
				forAll(coarseToFine, coarseI)
				{
					const labelList& fineFaces = coarseToFine[coarseI];
					coarseWeights[coarseI] = scalarList
					(
						fineFaces.size(),
						1.0 / fineFaces.size()
					);
				}

				patchFields.set
				(
					patchI,
					fvPatchField<Type>::New
					(
						vf.boundaryField()[patchI],
						boundary()[patchI],
						DimensionedField<Type, volMesh>::null(),
						agglomPatchFieldMapper(coarseToFine, coarseWeights, agglom.size())
					)
				);
			}
		}
		else
		{
			forAll(vf.boundaryField(), patchI)
			{
				labelList map(identity(vf.boundaryField()[patchI].size()));

				patchFields.set
				(
					patchI,
					fvPatchField<Type>::New
					(
						vf.boundaryField()[patchI],
						boundary()[patchI],
						DimensionedField<Type, volMesh>::null(),
						directPatchFieldMapper(map, map.size())
					)
				);
			}
		}

		// Create the complete field from the pieces
		tmp<GeometricField<Type, fvPatchField, volMesh> > tresF
		(
			new GeometricField<Type, fvPatchField, volMesh>
			(
				IOobject
				(
					vf.name(),
					time().timeName(),
					*this,
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				*this,
				vf.dimensions(),
				internalField,
				patchFields
				)
		);

		return tresF;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //