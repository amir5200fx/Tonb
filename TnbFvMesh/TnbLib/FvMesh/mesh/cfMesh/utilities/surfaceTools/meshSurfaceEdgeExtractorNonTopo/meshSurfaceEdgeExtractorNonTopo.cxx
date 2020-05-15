#include <meshSurfaceEdgeExtractorNonTopo.hxx>

#include <demandDrivenData.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	meshSurfaceEdgeExtractorNonTopo::meshSurfaceEdgeExtractorNonTopo
	(
		polyMeshGen& mesh,
		const meshOctree& octree
	)
		:
		mesh_(mesh),
		meshOctree_(octree)
	{
		decomposeBoundaryFaces();

		remapBoundaryPoints();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshSurfaceEdgeExtractorNonTopo::~meshSurfaceEdgeExtractorNonTopo()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //