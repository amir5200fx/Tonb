#include <meshSurfaceEdgeExtractorNonTopo.hxx>

#include <demandDrivenData.hxx>
#include <meshSurfaceEngine.hxx>
#include <meshSurfaceMapper.hxx>
#include <correctEdgesBetweenPatches.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshSurfaceEdgeExtractorNonTopo::decomposeBoundaryFaces()
	{
		correctEdgesBetweenPatches featureEdges(mesh_);
	}

	void meshSurfaceEdgeExtractorNonTopo::remapBoundaryPoints()
	{
		meshSurfaceEngine mse(mesh_);
		meshSurfaceMapper mapper(mse, meshOctree_);

		mapper.mapVerticesOntoSurfacePatches();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //