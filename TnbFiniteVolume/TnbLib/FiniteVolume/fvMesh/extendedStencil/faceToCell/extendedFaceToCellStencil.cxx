#include <extendedFaceToCellStencil.hxx>

#include <coupledPolyPatch.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedFaceToCellStencil::extendedFaceToCellStencil(const polyMesh& mesh)
	:
	mesh_(mesh)
{
	// Check for transformation - not supported.
	const polyBoundaryMesh& patches = mesh.boundaryMesh();

	forAll(patches, patchI)
	{
		if (isA<coupledPolyPatch>(patches[patchI]))
		{
			const coupledPolyPatch& cpp =
				refCast<const coupledPolyPatch>(patches[patchI]);

			if (!cpp.parallel() || cpp.separated())
			{
				FatalErrorIn
				(
					"extendedFaceToCellStencil::extendedFaceToCellStencil"
					"(const polyMesh&)"
				) << "Coupled patches with transformations not supported."
					<< endl
					<< "Problematic patch " << cpp.name() << exit(FatalError);
			}
		}
	}
}


// ************************************************************************* //