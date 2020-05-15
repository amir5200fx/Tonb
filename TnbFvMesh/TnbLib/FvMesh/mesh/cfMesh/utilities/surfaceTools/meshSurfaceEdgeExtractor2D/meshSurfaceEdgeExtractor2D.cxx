#include <meshSurfaceEdgeExtractor2D.hxx>

#include <demandDrivenData.hxx>
#include <meshSurfaceOptimizer.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from mesh, octree
	meshSurfaceEdgeExtractor2D::meshSurfaceEdgeExtractor2D
	(
		polyMeshGen& mesh,
		const meshOctree& octree
	)
		:
		mesh_(mesh),
		meshOctree_(octree)
	{}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshSurfaceEdgeExtractor2D::~meshSurfaceEdgeExtractor2D()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //