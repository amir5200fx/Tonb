#include <meshOptimizer.hxx>

#include <demandDrivenData.hxx>
#include <meshSurfaceEngine.hxx>
#include <meshSurfaceOptimizer.hxx>
#include <meshSurfaceMapper.hxx>
#include <meshOctree.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshOptimizer::optimizeSurface(const meshOctree& octree)
	{
		Info << "Optimizing positions of surface nodes" << endl;

		meshSurfaceEngine& mse = const_cast<meshSurfaceEngine&>(meshSurface());
		meshSurfaceOptimizer surfaceOptimizer(mse, octree);

		if (enforceConstraints_)
			surfaceOptimizer.enforceConstraints(badPointsSubsetName_);

		surfaceOptimizer.optimizeSurface();

		meshSurfaceMapper(mse, octree).mapVerticesOntoSurfacePatches();

		clearSurface();

		Info << "Finished optimizing positions of surface nodes" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //