#include <meshSurfacePartitioner.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	meshSurfacePartitioner::meshSurfacePartitioner
	(
		const meshSurfaceEngine& meshSurface
	)
		:
		meshSurface_(meshSurface),
		facePatch_(meshSurface.boundaryFacePatches()),
		pointPatches_(),
		corners_(),
		edgePoints_(),
		patchPatches_(),
		nEdgesAtPoint_(),
		featureEdges_()
	{
		calculateCornersEdgesAndAddressing();
	}

	meshSurfacePartitioner::meshSurfacePartitioner
	(
		const meshSurfaceEngine& meshSurface,
		const labelList& facePatch
	)
		:
		meshSurface_(meshSurface),
		facePatch_(facePatch),
		pointPatches_(),
		corners_(),
		edgePoints_(),
		patchPatches_(),
		nEdgesAtPoint_(),
		featureEdges_()
	{
		calculateCornersEdgesAndAddressing();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshSurfacePartitioner::~meshSurfacePartitioner()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //