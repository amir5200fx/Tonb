#include <topologicalCleaner.hxx>

#include <demandDrivenData.hxx>
#include <decomposeCells.hxx>
#include <checkCellConnectionsOverFaces.hxx>
#include <meshSurfaceEngine.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void topologicalCleaner::decomposeCells()
	{
		if (!changed_)
			return;

		tnbLib::decomposeCells dc(mesh_);
		dc.decomposeMesh(decomposeCell_);

	}
	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from points, cells, boundary faces, and octree
	topologicalCleaner::topologicalCleaner
	(
		polyMeshGen& mesh
	)
		:
		mesh_(mesh),
		changed_(false),
		decomposeCell_(mesh.cells().size(), false)
	{
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	topologicalCleaner::~topologicalCleaner()
	{
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	bool topologicalCleaner::cleanTopology()
	{
		checkInvalidConnectionsForVerticesCells();

		checkInvalidConnectionsForVerticesFaces();

		checkNonConsecutiveBoundaryVertices();

		checkNonMappableCells();

		checkNonMappableFaces();

		decomposeCells();

		if (checkCellConnectionsOverFaces(mesh_).checkCellGroups())
			changed_ = true;

		return changed_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //