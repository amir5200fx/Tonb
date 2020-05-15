#include <meshSurfaceEdgeExtractorFUN.hxx>

#include <meshSurfaceEngine.hxx>
#include <demandDrivenData.hxx>
#include <Pstream.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	meshSurfaceEngine& meshSurfaceEdgeExtractorFUN::surfaceEngine()
	{
# ifdef USE_OMP
		if (omp_in_parallel())
			FatalErrorIn
			(
				"meshSurfaceEngine& meshSurfaceEdgeExtractorFUN::surfaceEngine()"
			) << "Cannot create surface engine with a parallel region"
			<< exit(FatalError);
# endif

		if (!surfaceEnginePtr_)
			surfaceEnginePtr_ = new meshSurfaceEngine(mesh_);

		return *surfaceEnginePtr_;
	}

	void meshSurfaceEdgeExtractorFUN::clearOut()
	{
		deleteDemandDrivenData(surfaceEnginePtr_);
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from mesh and octree
	meshSurfaceEdgeExtractorFUN::meshSurfaceEdgeExtractorFUN
	(
		polyMeshGen& mesh,
		const meshOctree& octree,
		const bool createWrapperSheet
	)
		:
		mesh_(mesh),
		meshOctree_(octree),
		surfaceEnginePtr_(NULL),
		createWrapperSheet_(createWrapperSheet)
	{
		if (Pstream::parRun())
			FatalErrorIn
			(
				"meshSurfaceEdgeExtractorFUN::meshSurfaceEdgeExtractorFUN"
				"(polyMeshGen&, const meshOctree&)"
			) << "Cannot run in parallel!" << exit(FatalError);

		createBasicFundamentalSheets();

		smoothMeshSurface();

		remapBoundaryPoints();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshSurfaceEdgeExtractorFUN::~meshSurfaceEdgeExtractorFUN()
	{
		deleteDemandDrivenData(surfaceEnginePtr_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //