#include <correctEdgesBetweenPatches.hxx>

#include <demandDrivenData.hxx>
#include <meshSurfaceEngine.hxx>
#include <decomposeCells.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const meshSurfaceEngine& correctEdgesBetweenPatches::meshSurface() const
	{
		if (!msePtr_)
			msePtr_ = new meshSurfaceEngine(mesh_);

		return *msePtr_;
	}

	//- delete mesh surface
	void correctEdgesBetweenPatches::clearMeshSurface()
	{
		deleteDemandDrivenData(msePtr_);
	}

	void correctEdgesBetweenPatches::replaceBoundary()
	{
		clearMeshSurface();

		polyMeshGenModifier(mesh_).replaceBoundary
		(
			patchNames_,
			newBoundaryFaces_,
			newBoundaryOwners_,
			newBoundaryPatches_
		);
	}

	void correctEdgesBetweenPatches::decomposeCorrectedCells()
	{
		if (decompose_)
		{
			clearMeshSurface();

			decomposeCells dc(mesh_);
			dc.decomposeMesh(decomposeCell_);
		}
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from mesh
	correctEdgesBetweenPatches::correctEdgesBetweenPatches(polyMeshGen& mesh)
		:
		mesh_(mesh),
		msePtr_(NULL),
		patchNames_(mesh.boundaries().size()),
		patchTypes_(mesh.boundaries().size()),
		newBoundaryFaces_(),
		newBoundaryOwners_(),
		newBoundaryPatches_(),
		decomposeCell_(mesh_.cells().size(), false),
		decompose_(false)
	{
		const PtrList<boundaryPatch>& boundaries = mesh_.boundaries();
		forAll(boundaries, patchI)
		{
			patchNames_[patchI] = boundaries[patchI].patchName();
			patchTypes_[patchI] = boundaries[patchI].patchType();
		}

		//decomposeProblematicFaces();

		decomposeConcaveFaces();

		patchCorrection();

		decomposeCorrectedCells();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	correctEdgesBetweenPatches::~correctEdgesBetweenPatches()
	{
		deleteDemandDrivenData(msePtr_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //