#include <extendedFaceToCellStencil.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::extendedFaceToCellStencil::collectData
(
	const mapDistribute& map,
	const labelListList& stencil,
	const GeometricField<Type, fvsPatchField, surfaceMesh>& fld,
	List<List<Type> >& stencilFld
)
{
	// 1. Construct face data in compact addressing
	List<Type> compactFld(map.constructSize(), pTraits<Type>::zero);

	// Insert my internal values
	forAll(fld, cellI)
	{
		compactFld[cellI] = fld[cellI];
	}
	// Insert my boundary values
	label nCompact = fld.size();
	forAll(fld.boundaryField(), patchI)
	{
		const fvsPatchField<Type>& pfld = fld.boundaryField()[patchI];

		forAll(pfld, i)
		{
			compactFld[nCompact++] = pfld[i];
		}
	}

	// Do all swapping
	map.distribute(compactFld);

	// 2. Pull to stencil
	stencilFld.setSize(stencil.size());

	forAll(stencil, faceI)
	{
		const labelList& compactCells = stencil[faceI];

		stencilFld[faceI].setSize(compactCells.size());

		forAll(compactCells, i)
		{
			stencilFld[faceI][i] = compactFld[compactCells[i]];
		}
	}
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh> >
tnbLib::extendedFaceToCellStencil::weightedSum
(
	const mapDistribute& map,
	const labelListList& stencil,
	const GeometricField<Type, fvsPatchField, surfaceMesh>& fld,
	const List<List<scalar> >& stencilWeights
)
{
	const fvMesh& mesh = fld.mesh();

	// Collect internal and boundary values
	List<List<Type> > stencilFld;
	collectData(map, stencil, fld, stencilFld);

	tmp<GeometricField<Type, fvPatchField, volMesh> > tsfCorr
	(
		new GeometricField<Type, fvPatchField, volMesh>
		(
			IOobject
			(
				fld.name(),
				mesh.time().timeName(),
				mesh
			),
			mesh,
			dimensioned<Type>
			(
				fld.name(),
				fld.dimensions(),
				pTraits<Type>::zero
				)
			)
	);
	GeometricField<Type, fvPatchField, volMesh>& sf = tsfCorr();

	// cells
	forAll(sf, cellI)
	{
		const List<Type>& stField = stencilFld[cellI];
		const List<scalar>& stWeight = stencilWeights[cellI];

		forAll(stField, i)
		{
			sf[cellI] += stField[i] * stWeight[i];
		}
	}

	// Boundaries values?

	return tsfCorr;
}


// ************************************************************************* //