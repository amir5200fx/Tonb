#include <decomposeCells.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	decomposeCells::decomposeCells(polyMeshGen& mesh)
		:
		mesh_(mesh),
		patchNames_(mesh.boundaries().size()),
		patchTypes_(mesh.boundaries().size()),
		newBoundaryFaces_(),
		newBoundaryPatches_(),
		facesOfNewCells_()
	{
		const PtrList<boundaryPatch>& boundaries = mesh_.boundaries();
		forAll(boundaries, patchI)
		{
			patchNames_[patchI] = boundaries[patchI].patchName();
			patchTypes_[patchI] = boundaries[patchI].patchType();
		}
	}

	//- Destructor
	decomposeCells::~decomposeCells()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//

} // End namespace tnbLib

// ************************************************************************* //