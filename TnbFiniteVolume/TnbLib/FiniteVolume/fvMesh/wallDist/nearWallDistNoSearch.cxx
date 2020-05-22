#include <nearWallDistNoSearch.hxx>

#include <fvMesh.hxx>
#include <wallPoint.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::nearWallDistNoSearch::doAll()
{
	const volVectorField& cellCentres = mesh_.C();
	const fvPatchList& patches = mesh_.boundary();

	forAll(patches, patchI)
	{
		fvPatchScalarField& ypatch = operator[](patchI);

		if (patches[patchI].isWall())
		{
			const unallocLabelList& faceCells = patches[patchI].faceCells();

			const fvPatchVectorField& patchCentres
				= cellCentres.boundaryField()[patchI];

			const fvsPatchVectorField& Apatch
				= mesh_.Sf().boundaryField()[patchI];

			const fvsPatchScalarField& magApatch
				= mesh_.magSf().boundaryField()[patchI];

			forAll(patchCentres, facei)
			{
				ypatch[facei] =
					(
						Apatch[facei] &
						(
							patchCentres[facei]
							- cellCentres[faceCells[facei]]
							)
						) / magApatch[facei];
			}
		}
		else
		{
			ypatch = 0.0;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nearWallDistNoSearch::nearWallDistNoSearch(const tnbLib::fvMesh& mesh)
	:
	volScalarField::GeometricBoundaryField
	(
		mesh.boundary(),
		mesh.V(),           // Dummy internal field
		calculatedFvPatchScalarField::typeName
	),
	mesh_(mesh)
{
	doAll();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::nearWallDistNoSearch::~nearWallDistNoSearch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::nearWallDistNoSearch::correct()
{
	if (mesh_.changing())
	{
		// Update size of GeometricBoundaryField
		forAll(mesh_.boundary(), patchI)
		{
			operator[](patchI).setSize(mesh_.boundary()[patchI].size());
		}
	}

	doAll();
}


// ************************************************************************* //